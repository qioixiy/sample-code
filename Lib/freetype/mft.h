// mft.h
#ifndef __mtf_h__
#define __mtf_h__

#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <sstream>

#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>

#include <GL/glut.h>


#ifdef _MSC_VER
#endif

#ifdef __GNUC__
#include <unistd.h>
#endif


namespace freetype
{
using namespace std;

int next_p2(int a);
int splite(const std::string &line,const std::string & s, std::vector<std::string> &vlist);

template <typename T>
void strtonumber(const std::string& value,T &data);
/**
 *
 * 思路是：
 * 1.读取文件
 * 2.把英文字母，字符，符号这些单字符转换成纹理
 * 3.显示字符串，
 *    A 获取字符串中的数据，进行一个一个字符或文字进行获取，
 *    B 如果是文字，获取文字freetype索引，生成纹理，
 *        保存gl的texture,显示列表和文字字符到std::map 已准相同文字的时候查询
 *    C 拼接要使用的纹理索引列表，记录纹理数量
 *    D 真正的绘制了(这里还是使用显示列表来进行)
 */
typedef struct STF_TEXTURE_DATA
{
    GLuint m_list;
    GLuint m_texture;
    STF_TEXTURE_DATA():m_list(0),m_texture(0){}
}STF_TEXTURE_DATA;

// 这个是使用到的显示列表
typedef struct STF_LIST
{
    int size;    // 现实列表的长度
    GLuint *m_list;    // 这个是一个显示列表集合
}STF_LIST;

class MFont_Data
{
    public:
        MFont_Data();
        ~MFont_Data();

        void init(const char *filename, int h);
        void clean();

        void drawtext(float x, float y, const char *fmt, ...);
        void drawonetext(float x, float y, const char *fmt, ...);

    protected:
        void drawlinetext(vector<FT_ULong> &list);
        // 创建字符和英文等单字符的文字生成静态纹理
        // 生成单个
        void make_dlist(FT_Face face, char ch, GLuint list_base, GLuint* tex_base);
        void make_wlist(FT_Face face, FT_ULong ch, GLuint list, GLuint texture); 
       
        //void maie_one(FT_Face face, FT_ULong ch, GLuint list, GLuint texture);

        /////////////////////////////////////////////
        // 辅助函数部分
        // 判断是否已经创建过这个文字的纹理，这里只针对多字符，
        // 单字符直接从显示列表里面拿就好了
        bool hasTexListData(FT_ULong ch, STF_TEXTURE_DATA& data);
        void createTexListData(FT_ULong ch, STF_TEXTURE_DATA& data);

        inline void pushScreenCoordinateMatrix();
        inline void pop_projection_matrix();

        // 单个字符串，不要有\n的
        inline int getULongList(const std::string& line, vector<FT_ULong> &list);

        // 判断是字符还是多字节文字
        inline int getUtf8Size(char c);
        // 因为freetype 中使用的是unicode ,而不是 utf8 悲剧中
        inline FT_ULong utf8tounicode(char *s, int size);
       
        // 这个是我们当前现实使用的字符串，如果有变化就需要从新生成
        bool m_isChange;    // 是否需要改变
        //string m_string;
        vector<GLuint> m_textureVect;
   
        //vector<FT_ULong> m_chVect;    // 保存需要的所有字符

        //vector<STF_LIST> m_drawVect;    // 这个就是用来绘制的东西了
        float m_h; // 字体的高度
       
        GLuint *m_textures;    // 字体使用的纹理 只针对英文字母数字，单字符符号
        GLuint m_list_base;    // 显示列表的值
   
        FT_Library    m_library;
        FT_Face        m_face;   
        ////////////////////////////////////////
        // 保存所有的文字的map
        map<FT_ULong,FT_UInt>            m_allcharactorMap;// 文字对应的glyph索引
        map<FT_ULong,STF_TEXTURE_DATA>    m_ch2texlistMap;// 文字对应的纹理,这里只针对文字部分,字符那128里面


};
}
// 使用方法
//
// #include "mft.h"
// using namespace freetype;
// MFont_Data our_font;
//
// our_font.init("simhei.ttf",16);
// our_font.drawtext("Active 中文 FreeType Text - %7.2f", g_angle);
// our_font.clean();
//
#endif // __mtf_h__
