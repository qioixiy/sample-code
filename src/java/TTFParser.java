// import java.io.File;
// import java.io.IOException;
// import java.io.InputStream;
   
// import java.util.ArrayList;
// import java.util.Iterator;
// import java.util.List;
   
// /**
//  * A true type font file parser.
//  * 
//  * @author Ben Litchfield (ben@benlitchfield.com)
//  * @version $Revision: 1.2 $
//  */
// public class TTFParser
// {   
//     /**
//      * A simple command line program to test parsing of a TTF file. <br/>
//      * usage: java org.pdfbox.ttf.TTFParser &lt;ttf-file&gt;
//      * 
//      * @param args The command line arguments.
//      * 
//      * @throws IOException If there is an error while parsing the font file.
//      */
//     public static void main( String[] args ) throws IOException
//     {
//         if( args.length != 1 )
//             {
//                 System.err.println( "usage: java org.pdfbox.ttf.TTFParser <ttf-file>" );
//                 System.exit( -1 );
//             }
//         TTFParser parser = new TTFParser();
//         TrueTypeFont font = parser.parseTTF( args[0] );
//         System.out.println( "Font:" + font );
//     }
       
//     /**
//      * Parse a file and get a true type font.
//      * @param ttfFile The TTF file.
//      * @return A true type font.
//      * @throws IOException If there is an error parsing the true type font.
//      */
//     public TrueTypeFont parseTTF( String ttfFile ) throws IOException
//     {
//         RAFDataStream raf = new RAFDataStream( ttfFile, "r" );
//         return parseTTF( raf );
//     }
       
//     /**
//      * Parse a file and get a true type font.
//      * @param ttfFile The TTF file.
//      * @return A true type font.
//      * @throws IOException If there is an error parsing the true type font.
//      */
//     public TrueTypeFont parseTTF( File ttfFile ) throws IOException
//     {
//         RAFDataStream raf = new RAFDataStream( ttfFile, "r" );
//         return parseTTF( raf );
//     }
       
//     /**
//      * Parse a file and get a true type font.
//      * @param ttfData The TTF data to parse.
//      * @return A true type font.
//      * @throws IOException If there is an error parsing the true type font.
//      */
//     public TrueTypeFont parseTTF( InputStream ttfData ) throws IOException
//     {
//         return parseTTF( new MemoryTTFDataStream( ttfData ));
//     }
       
//     /**
//      * Parse a file and get a true type font.
//      * @param raf The TTF file.
//      * @return A true type font.
//      * @throws IOException If there is an error parsing the true type font.
//      */
//     public TrueTypeFont parseTTF( TTFDataStream raf ) throws IOException
//     {
//         TrueTypeFont font = new TrueTypeFont( raf );
//         font.setVersion( raf.read32Fixed() );
//         int numberOfTables = raf.readUnsignedShort();
//         int searchRange = raf.readUnsignedShort();
//         int entrySelector = raf.readUnsignedShort();
//         int rangeShift = raf.readUnsignedShort();
//         for( int i=0; i<numberOfTables; i++ )
//             {
//                 TTFTable table = readTableDirectory( raf );   
//                 font.addTable( table );
//             }
//         List<TTFTable> initialized = new ArrayList<TTFTable>();
//         //need to initialize a couple tables in a certain order
//         HeaderTable head = font.getHeader();
//         raf.seek( head.getOffset() );
//         head.initData( font, raf );
//         initialized.add( head );
           
           
//         HorizontalHeaderTable hh = font.getHorizontalHeader();
//         raf.seek( hh.getOffset() );
//         hh.initData( font, raf );
//         initialized.add( hh );
           
//         MaximumProfileTable maxp = font.getMaximumProfile();
//         raf.seek( maxp.getOffset() );
//         maxp.initData( font, raf );
//         initialized.add( maxp );
           
//         PostScriptTable post = font.getPostScript();
//         raf.seek( post.getOffset() );
//         post.initData( font, raf );
//         initialized.add( post );
           
//         IndexToLocationTable loc = font.getIndexToLocation();
//         raf.seek( loc.getOffset() );
//         loc.initData( font, raf );
//         initialized.add( loc );
           
//         Iterator<TTFTable> iter = font.getTables().iterator();
//         while( iter.hasNext() )
//             {
//                 TTFTable table = iter.next();
//                 if( !initialized.contains( table ) )
//                     {
//                         raf.seek( table.getOffset() );
//                         table.initData( font, raf );
//                     }
//             }
//         return font;
//     }
       
//     private TTFTable readTableDirectory( TTFDataStream raf ) throws IOException
//     {
//         TTFTable retval = null;
//         String tag = raf.readString( 4 );
//         if( tag.equals( CMAPTable.TAG ) )
//             {
//                 retval = new CMAPTable();
//             }
//         else if( tag.equals( GlyphTable.TAG ) )
//             {
//                 retval = new GlyphTable();
//             }
//         else if( tag.equals( HeaderTable.TAG ) )
//             {
//                 retval = new HeaderTable();
//             }
//         else if( tag.equals( HorizontalHeaderTable.TAG ) )
//             {
//                 retval = new HorizontalHeaderTable();
//             }
//         else if( tag.equals( HorizontalMetricsTable.TAG ) )
//             {
//                 retval = new HorizontalMetricsTable();
//             }
//         else if( tag.equals( IndexToLocationTable.TAG ) )
//             {
//                 retval = new IndexToLocationTable();
//             }
//         else if( tag.equals( MaximumProfileTable.TAG ) )
//             {
//                 retval = new MaximumProfileTable();
//             }
//         else if( tag.equals( NamingTable.TAG ) )
//             {
//                 retval = new NamingTable();
//             }
//         else if( tag.equals( OS2WindowsMetricsTable.TAG ) )
//             {
//                 retval = new OS2WindowsMetricsTable();
//             }
//         else if( tag.equals( PostScriptTable.TAG ) )
//             {
//                 retval = new PostScriptTable();
//             }
//         else if( tag.equals( GlyphTable.TAG ) )
//             {
//                 retval = new GlyphTable();
//             }
//         else if( tag.equals( GlyphTable.TAG ) )
//             {
//                 retval = new GlyphTable();
//             }
//         else if( tag.equals( DigitalSignatureTable.TAG ) )
//             {
//                 retval = new DigitalSignatureTable();
//             }
//         else
//             {
//                 //unknown table type but read it anyway.
//                 retval = new TTFTable();
//             }
//         retval.setTag( tag );
//         retval.setCheckSum( raf.readUnsignedInt() );
//         retval.setOffset( raf.readUnsignedInt() );
//         retval.setLength( raf.readUnsignedInt() );
//         return retval;
//     }
// }

import java.io.File;
import java.io.IOException;
//import java.io.Exception;

import java.io.RandomAccessFile;

import java.nio.charset.Charset;

import java.util.HashMap;

import java.util.Map;
import java.io.FilenameFilter;
      

/**

 * TTF Font file parser

 * <p>

 * sample:

 * <code><pre>

 *                          File fs = new File("C:\\Windows\\Fonts");

 *                          File[] files = fs.listFiles(new FilenameFilter() {

 *                              public boolean accept(File dir, String name) {

 *                                  if (name.endsWith("ttf")){ return true;}

 *                                  return false;

 *                              }

 *                          });

 *                          for (File file : files) {

 *                              TTFParser parser = new TTFParser();

 *                              parser.parse(file.getAbsolutePath());

 *                              System.out.println("font name: " + parser.getFontName());

 *                          }

 * </pre></code>

 * <p/>

 * Copyright: Copyright (c) 12-8-6 下午3:51

 * <p/>

 * Version: 1.0

 * <p/>

 */

public class TTFParser {

    public static int COPYRIGHT = 0;

    public static int FAMILY_NAME = 1;

    public static int FONT_SUBFAMILY_NAME = 2;

    public static int UNIQUE_FONT_IDENTIFIER = 3;

    public static int FULL_FONT_NAME = 4;

    public static int VERSION = 5;

    public static int POSTSCRIPT_NAME = 6;

    public static int TRADEMARK = 7;

    public static int MANUFACTURER = 8;

    public static int DESIGNER = 9;

    public static int DESCRIPTION = 10;

    public static int URL_VENDOR = 11;

    public static int URL_DESIGNER = 12;

    public static int LICENSE_DESCRIPTION = 13;

    public static int LICENSE_INFO_URL = 14;

         

    private Map<Integer, String> fontProperties = new HashMap<Integer, String>();

 

    /**

     * 获取ttf font name

     * @return

     */

    public String getFontName() {

        if (fontProperties.containsKey(FULL_FONT_NAME)) {

            return fontProperties.get(FULL_FONT_NAME);

        } else if (fontProperties.containsKey(FAMILY_NAME)) {

            return fontProperties.get(FAMILY_NAME);

        } else {

            return null;

        }

    }

                 

    /**

     * 获取ttf属性

     * @param nameID 属性标记，见静态变量

     * @return 属性值

     */

    public String getFontPropertie(int nameID) {

        if (fontProperties.containsKey(nameID)) {

            return fontProperties.get(nameID);

        } else { return null; }

    }

           

    /**

     * 获取ttf属性集合

     * @return 属性集合(MAP)

     */

          

    public Map<Integer, String> getFontProperties() { return fontProperties; }

           

    /**

     * 执行解析

     * @param fileName ttf文件名

     * @throws IOException

     */

    public void parse(String fileName) throws IOException {

        fontProperties.clear();

        RandomAccessFile f = null;

        try {

            f = new RandomAccessFile(fileName, "r");

            parseInner(f);

        } finally {

            try {

                f.close();

            }catch (Exception e) {

                //ignore;

            }

        }

    }

    private void parseInner(RandomAccessFile randomAccessFile) throws IOException {

        int majorVersion = randomAccessFile.readShort();

        int minorVersion = randomAccessFile.readShort();

        int numOfTables = randomAccessFile.readShort();

        if (majorVersion != 1 || minorVersion != 0) { return; }

 

        //jump to TableDirectory struct

        randomAccessFile.seek(12);

                 

        boolean found = false;

        byte[] buff = new byte[4];

        TableDirectory tableDirectory = new TableDirectory();

        for (int i = 0; i < numOfTables; i++) {

            randomAccessFile.read(buff);

            tableDirectory.name = new String(buff);

            tableDirectory.checkSum = randomAccessFile.readInt();

            tableDirectory.offset = randomAccessFile.readInt();

            tableDirectory.length = randomAccessFile.readInt();

            if ("name".equalsIgnoreCase(tableDirectory.name)) {

                found = true;

                break;

            }else if (tableDirectory.name == null || tableDirectory.name.length() == 0) {

                break;

            }

        } 

                   

        // not found table of name

        if (!found) { return; }

        randomAccessFile.seek(tableDirectory.offset);

        NameTableHeader nameTableHeader = new NameTableHeader();

        nameTableHeader.fSelector = randomAccessFile.readShort();

        nameTableHeader.nRCount = randomAccessFile.readShort();

        nameTableHeader.storageOffset = randomAccessFile.readShort();

        NameRecord nameRecord = new NameRecord();

        for (int i = 0; i < nameTableHeader.nRCount; i++) {

            nameRecord.platformID = randomAccessFile.readShort();

            nameRecord.encodingID = randomAccessFile.readShort();

            nameRecord.languageID = randomAccessFile.readShort();

            nameRecord.nameID = randomAccessFile.readShort();

            nameRecord.stringLength = randomAccessFile.readShort();

            nameRecord.stringOffset = randomAccessFile.readShort();

            long pos = randomAccessFile.getFilePointer();

            byte[] bf = new byte[nameRecord.stringLength];

            long vpos = tableDirectory.offset + nameRecord.stringOffset + nameTableHeader.storageOffset;

            randomAccessFile.seek(vpos);

            randomAccessFile.read(bf);

            String temp = new String(bf, Charset.forName("utf-16"));

            fontProperties.put(nameRecord.nameID, temp);

            randomAccessFile.seek(pos);

        }

    }

    @Override
    public String toString() {

        return fontProperties.toString();

    }

    private static class TableDirectory {

        String name; //table name

        int checkSum; //Check sum

        int offset; //Offset from beginning of file

        int length; //length of the table in bytes

    }

 

    private static class NameTableHeader {

        int fSelector; //format selector. Always 0

        int nRCount; //Name Records count

        int storageOffset; //Offset for strings storage,

    }

 

    private static class NameRecord {

        int platformID;

        int encodingID;

        int languageID;

        int nameID;

        int stringLength;

        int stringOffset; //from start of storage area

    }

    public static void main(String[] args) {
        File fs = new File(args[0]);
        File[] files = fs.listFiles(new FilenameFilter() {
                public boolean accept(File dir, String name) {
                    if (name.endsWith("ttf")){ return true;}
                    return false;
                }
            });

        for (File file : files) {
            TTFParser parser = new TTFParser();
            try {
                parser.parse(file.getAbsolutePath());
            } catch (Exception e){
                ;
            }finally {
                ;
            }
            System.out.println("font name: " + parser.getFontName());
        }
    }
}
