// mft.cpp

#include "mft.h"
#include <iostream>

namespace freetype
{

//----------------------------------------------------------------------------------------
// 字符串分割函数
int splite(const std::string &line,const std::string & s, std::vector<std::string> &vlist)
{
    if (line == "")
        return -1;


    // 去掉两边的空格
    //line.erase(0, line.find_first_not_of("\t\n\r")).erase(line.find_last_not_of("\t\n\r") + 1);

    unsigned int len = s.size();
    unsigned int spos = 0;    // 分割的位置
    unsigned int rpos = 0;    // 读取数据的位置

    do{

        spos = line.find(s, rpos);
        vlist.push_back(line.substr(rpos, spos - rpos));
        rpos = spos + len;

    }while(spos != std::string::npos);

    return 0;
}

    //----------------------------------
    //
    int next_p2(int a)
    {
        int rval = 1;
        while(rval<a) rval <<= 1;
        return rval;
    }

//----------------------------------------------------------------------------------------
// 字符串转数字
template <typename T>
void strtonumber(const std::string& value,T &data)
{
    std::stringstream ss;
    ss << value;
    ss >> data;
}

    //-------------------------------------------------------
    //
    MFont_Data::MFont_Data()
    {
    }

    //-------------------------------------------------------
    //
    MFont_Data::~MFont_Data(){}
   
    //--------------------------------------------------------
    //
    void MFont_Data::init(const char *filename, int h)
    {
        // 英文字母，字符，等单个字符的纹理
        this->m_textures = new GLuint[128];
        this->m_h = h; // 字的高度

        if (FT_Init_FreeType(&m_library))
            throw std::runtime_error("FT_Init_FreeType failed");

        if (FT_New_Face(m_library, filename, 0, &m_face))
            throw std::runtime_error("FT_New_Face failed ( \
                there is probably a problem with your \
                    font file)");

        FT_Set_Char_Size(m_face, h << 6, h << 6, 96, 96);

        m_list_base = glGenLists(128);
        glGenTextures(128, m_textures);

        for (unsigned char i = 0; i < 128; i++)
            make_dlist(m_face, i, m_list_base, m_textures);


        // 单个字符的 128 个已经完成
        // 下面是加载所有的字符了
        FT_ULong charcode;
        FT_UInt gindex;

        charcode = FT_Get_First_Char(m_face, &gindex);
        while(gindex != 0)
        {
            m_allcharactorMap[charcode] = gindex;
            charcode = FT_Get_Next_Char(m_face, charcode, &gindex);
        }

    }

    //--------------------------------------------------------
    //
    void MFont_Data::clean()
    {
        FT_Done_Face(m_face);
        FT_Done_FreeType(m_library);

        glDeleteLists(m_list_base, 128);
        glDeleteTextures(128, m_textures);
        delete [] m_textures;
       
        //
        map<FT_ULong,STF_TEXTURE_DATA>::iterator iter;
        for (iter = m_ch2texlistMap.begin(); iter != m_ch2texlistMap.end(); iter++)
        {
            STF_TEXTURE_DATA tmpdata = iter->second;
            glDeleteLists(tmpdata.m_list,1);
            glDeleteTextures(1,&tmpdata.m_texture);
        }
        m_ch2texlistMap.clear();
        m_allcharactorMap.clear();
       
    }

    //----------------------------------------------------------
    // 这里处理的是单个字符的情况
    void MFont_Data::make_dlist(FT_Face face, char ch,
            GLuint list_base, GLuint * tex_base)
    {
        if (FT_Load_Glyph(face, FT_Get_Char_Index(face,ch),FT_LOAD_DEFAULT))
        {
            throw std::runtime_error("FT_Load_Glyph failed");
        }

        FT_Glyph glyph;
        if (FT_Get_Glyph(face->glyph, &glyph))
            throw std::runtime_error("FT_Get_Glyph failed");

        FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal,0, 1);
        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

        FT_Bitmap& bitmap = bitmap_glyph->bitmap;
        // 我们需要获取位图的信息
        int width = next_p2(bitmap.width);
        int height = next_p2(bitmap.rows);

        GLubyte* expanded_data = new GLubyte[2 * width * height];

        for(int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                expanded_data[2 *(i+j*width)] = expanded_data[2*(i+j*width)+1] =
                    (i >= bitmap.width || j >= bitmap.rows) ?
                    0 : bitmap.buffer[i + bitmap.width * j];
            }
        }

        // 设置纹理啦
        glBindTexture(GL_TEXTURE_2D, tex_base[ch]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA,
                GL_UNSIGNED_BYTE, expanded_data);

        delete [] expanded_data;

        glNewList(list_base + ch, GL_COMPILE);
        glBindTexture(GL_TEXTURE_2D, tex_base[ch]);
        glPushMatrix();

        glTranslatef(bitmap_glyph->left, 0, 0);
        glTranslatef(0, bitmap_glyph->top-bitmap.rows, 0);

        float x=(float)bitmap.width / (float)width;
        float y = (float)bitmap.rows / (float) height;

        glBegin(GL_QUADS);
            glTexCoord2d(0,0); glVertex2f(0,bitmap.rows);
            glTexCoord2d(0,y); glVertex2f(0,0);
            glTexCoord2d(x,y); glVertex2f(bitmap.width,0);
            glTexCoord2d(x,0); glVertex2f(bitmap.width,bitmap.rows);
        glEnd();
        glPopMatrix();
        glTranslatef(face->glyph->advance.x >> 6 ,0,0);

        glEndList();
    }

    //-------------------------------------------------------------
    // 处理多字符的情况
    void MFont_Data::make_wlist(FT_Face face, FT_ULong ch,
            GLuint list, GLuint texture)
    {
        if (FT_Load_Glyph(face, FT_Get_Char_Index(face,ch),FT_LOAD_DEFAULT))
        {
            throw std::runtime_error("FT_Load_Glyph failed");
        }

        FT_Glyph glyph;

        if (FT_Get_Glyph(face->glyph, &glyph))
            throw std::runtime_error("FT_Get_Glyph failed");

        FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal,0, 1);
        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

        FT_Bitmap& bitmap = bitmap_glyph->bitmap;
        // 我们需要获取位图的信息
        int width = next_p2(bitmap.width);
        int height = next_p2(bitmap.rows);

        GLubyte* expanded_data = new GLubyte[2 * width * height];

        for(int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                expanded_data[2 *(i+j*width)] = expanded_data[2*(i+j*width)+1] =
                    (i >= bitmap.width || j >= bitmap.rows) ?
                    0 : bitmap.buffer[i + bitmap.width * j];
            }
        }

        // 设置纹理啦
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA,
                GL_UNSIGNED_BYTE, expanded_data);

        delete [] expanded_data;

        glNewList(list, GL_COMPILE);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPushMatrix();

        glTranslatef(bitmap_glyph->left, 0, 0);
        glTranslatef(0, bitmap_glyph->top-bitmap.rows, 0);

        float x = (float)bitmap.width / (float)width;
        float y = (float)bitmap.rows / (float) height;

        glBegin(GL_QUADS);
            glTexCoord2d(0,0); glVertex2f(0,bitmap.rows);
            glTexCoord2d(0,y); glVertex2f(0,0);
            glTexCoord2d(x,y); glVertex2f(bitmap.width,0);
            glTexCoord2d(x,0); glVertex2f(bitmap.width,bitmap.rows);
        glEnd();
        glPopMatrix();
        glTranslatef(face->glyph->advance.x >> 6 ,0,0);

        glEndList();

        // 保存需要的信息
        STF_TEXTURE_DATA tmpdata;
       
        tmpdata.m_list = list;
        tmpdata.m_texture = texture;
       
        m_ch2texlistMap[ch] = tmpdata;
    }

    bool MFont_Data::hasTexListData(FT_ULong ch, STF_TEXTURE_DATA &data)
    {
        map<FT_ULong,STF_TEXTURE_DATA>::iterator iter = m_ch2texlistMap.find(ch);
       if (iter != m_ch2texlistMap.end())
       {
           data = iter->second;
           return true;
       }      
       return false;
    }

    //-------------------------------------------------------------
    //
    void MFont_Data::drawtext(float x, float y, const char *fmt, ...)
    {
        pushScreenCoordinateMatrix();
       
        char text[256];
        char buff[256];

        memset(text, 0, 256);
        memset(buff, 0, 256);

        float h = m_h/ 0.63f;
        va_list ap;

        if (fmt == NULL)
            *text = 0;
        else
        {
            va_start(ap, fmt);
            vsprintf(text, fmt, ap);
            va_end(ap);
        }
        string s(text);

        /////////////
        vector<string> vlist;
        splite(s,"\n", vlist);

        glPushAttrib(GL_LIST_BASE | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
        glMatrixMode(GL_MODELVIEW);
        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //glListBase(m_list_base);
        float modelview_matrix[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

        for (unsigned int i = 0; i < vlist.size(); i++)
        {
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(x, y-h*i, 0);
            glMultMatrixf(modelview_matrix);

            vector<FT_ULong> ftlist;
            getULongList(vlist[i], ftlist);   
            drawlinetext(ftlist);

            glPopMatrix();
        }

        glPopAttrib();
        pop_projection_matrix();
    }
   
    //------------------------------------------------------
    //
    void MFont_Data::drawonetext(float x, float y, const char *fmt, ...)
    {

        pushScreenCoordinateMatrix();

        //GLuint font = ft_font.list_base;
        float h = m_h/ 0.63f;
        char text[256];
        va_list ap;

        if (fmt == NULL)
            *text = 0;
        else
        {
            va_start(ap, fmt);
            vsprintf(text, fmt, ap);
            va_end(ap);
        }

        const char *start_line = text;
        const char *c = text;
        vector<string> lines;
        //int len = getUtf8Size(c[0]);   
        for (; *c; c++)
        {
            if (*c == '\n')
            {
                string line;
                for (const char *n=start_line; n < c; n++)
                    line.append(1, *n);

                lines.push_back(line);
                start_line=c+1;
            }
        }

        if (start_line)
        {
            string line;
            for(const char *n = start_line; n<c; n++)
                line.append(1,*n);

            lines.push_back(line);
        }

        glPushAttrib(GL_LIST_BASE | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
        glMatrixMode(GL_MODELVIEW);
        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glListBase(m_list_base);
        float modelview_matrix[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

        for (unsigned int i = 0; i < lines.size(); i++)
        {
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(x, y-h*i, 0);
            glMultMatrixf(modelview_matrix);

            glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
            glPopMatrix();
        }

        glPopAttrib();
        pop_projection_matrix();
    }
    //--------------------------------------------------------
    //
    void MFont_Data::drawlinetext(vector<FT_ULong> &list)
    {
        GLuint tmplist[list.size()];

        for (unsigned int i = 0; i < list.size(); i++)
        {
            if (list[i] > 128) // 判断下
            {
                STF_TEXTURE_DATA tmpdata;
                if (hasTexListData(list[i], tmpdata))
                {
                    tmplist[i] = tmpdata.m_list;
                    //glCallList(tmpdata.m_list);
                }   
                else
                {
                    createTexListData(list[i], tmpdata);
                    tmplist[i] = tmpdata.m_list;
                    //glCallList(tmpdata.m_list);
                }
            }
            else
            {
                tmplist[i] = m_list_base + list[i]; // 直接使用字符和英文字符的纹理了
                //glCallList(m_list_base + list[i]);
                //glCallList(list[i]);
            }
        }       

        // 获取了所有的显示列表 开始显示 数据
        // 这里可能要一个一个调用哦 如果下面的这个函数无法实现的话
        glCallLists(list.size(), GL_UNSIGNED_INT, tmplist);   

    }

    //---------------------------------------------------------
    //
    void MFont_Data::createTexListData(FT_ULong ch, STF_TEXTURE_DATA& data)
    {
        data.m_list = glGenLists(1);
        glGenTextures(1, &data.m_texture);

        make_wlist(m_face, ch, data.m_list, data.m_texture);
    }

    //--------------------------------------------------
    //
    void MFont_Data::pushScreenCoordinateMatrix()
    {
        glPushAttrib(GL_TRANSFORM_BIT);
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
        glPopAttrib();
    }

    //---------------------------------------------------
    //
    void MFont_Data::pop_projection_matrix()
    {
        glPushAttrib(GL_TRANSFORM_BIT);
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glPopAttrib();
    }

    //----------------------------------------------------
    //
    int MFont_Data::getULongList(const std::string& line, vector<FT_ULong> &list)
    {
        if (line == "")
            return 0;

        char buff[256];

        unsigned int len = line.size();
       
        unsigned int i = 0;
        FT_ULong tmpdata = 0;

        while(i < len)
        {
            char c = line[i];
            int size = getUtf8Size(c);

            if (size > 0)
            {
                memset(buff, 0, 256);
                unsigned int count = i + size;
                unsigned int k = 0;
                while (i < count)
                {
                    buff[k]     = line[i];
                    k++;
                    i++;
                }

                tmpdata = utf8tounicode(buff,size);   
            }
            else
            {
                tmpdata = line[i];
                i++;
            }
            list.push_back(tmpdata);
        } // while
        return 0;
    }
   
    //--------------------------------------------------------
    //
    int MFont_Data::getUtf8Size(char c)
    {
        char t = 1 << 7;
        char r = c;
        int count = 0;
        while (r & t)
        {
            r = r << 1;
            count++;
        }
        return count;
    }

    //-----------------------------------------------------
    //
    FT_ULong MFont_Data::utf8tounicode(char *s, int size)
    {
        char uc[] = {0x7f,0x3f,0x1f,0x0f,0x07,0x03};

        FT_ULong data = 0;
        FT_ULong tmp = 0;
        int count = 0;

        char *p = s;
        while (count < size)
        {
            char c = (*p);
            tmp = c;

            if (count == 0)
            {
                tmp &= uc[size - 1];
            }
            else
            {
                tmp &= 0x3f;
            }

            tmp = tmp << (6 * (size - count - 1));
            data |= tmp;

            p++;
            count++;
        }

        return data;
    }

}
