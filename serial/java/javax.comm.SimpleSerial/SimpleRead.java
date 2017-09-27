import java.io.*;
import java.util.*;
import javax.comm.*;
public class SimpleRead implements Runnable, SerialPortEventListener {
    static CommPortIdentifier portId;
    //枚举类
    static Enumeration portList;
    InputStream inputStream;
    SerialPort serialPort;
    Thread readThread;
    public static void main(String[] args) {
        portList = CommPortIdentifier.getPortIdentifiers();
        /*不带参数的getPortIdentifiers方法获得一个枚举对象，该对象又包含了系统中管理每个端口的CommPortIdentifier对象。
          注意这里的端口不仅仅是指串口，也包括并口。这个方法还可以带参数。getPortIdentifiers(CommPort)获得与已经被应
          用程序打开的端口相对应的CommPortIdentifier对象。getPortIdentifier(String portName)获取指定端口名（比如“COM1”）
          的CommPortIdentifier对象。*/
        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            /*getPortType方法返回端口类型*/
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                /* 找Windows下的第一个串口*/
                if (portId.getName().equals("COM1")) {
                    /*找Unix-like系统下的第一个串口*/
                    //if (portId.getName().equals("/dev/term/a")) {
                    SimpleRead reader = new SimpleRead();
                }
            }
        }
    }
    public SimpleRead() {
        try {
            /* open方法打开通讯端口，获得一个CommPort对象。它使程序独占端口。如果端口正被其他应用程序占用，将使用
               CommPortOwnershipListener事件机制，传递一个PORT_OWNERSHIP_REQUESTED事件。每个端口都关联一个
               InputStream和一个OutputStream。如果端口是用open方法打开的，那么任何的getInputStream都将返回
               相同的数据流对象，除非有close被调用。有两个参数，第一个为应用程序名；第二个参数是在端口打开
               时阻塞等待的毫秒数。 */
            serialPort = (SerialPort) portId.open("SimpleReadApp", 2000);
        } catch (PortInUseException e) {}
        try {
            /*获取端口的输入流对象*/
            inputStream = serialPort.getInputStream();
        } catch (IOException e) {}
        try {
            /*注册一个SerialPortEventListener事件来监听串口事件*/
            serialPort.addEventListener(this);
        } catch (TooManyListenersException e) {}
        /*数据可用*/
        serialPort.notifyOnDataAvailable(true);
        try {
            /*设置串口初始化参数，依次是波特率，数据位，停止位和校验*/
            serialPort.setSerialPortParams(9600,
                                           SerialPort.DATABITS_8,
                                           SerialPort.STOPBITS_1,
                                           SerialPort.PARITY_NONE);
        } catch (UnsupportedCommOperationException e) {}
        readThread = new Thread(this);
        readThread.start();
    }
    public void run() {
        try {
            Thread.sleep(20000);
        } catch (InterruptedException e) {}
    }
    //串口事件
    public void serialEvent(SerialPortEvent event) {
        switch(event.getEventType()) {
        case SerialPortEvent.BI:/*Break interrupt,通讯中断*/
        case SerialPortEvent.OE:/*Overrun error，溢位错误*/
        case SerialPortEvent.FE:/*Framing error，传帧错误*/
        case SerialPortEvent.PE:/*Parity error，校验错误*/
        case SerialPortEvent.CD:/*Carrier detect，载波检测*/
        case SerialPortEvent.CTS:/*Clear to send，清除发送*/
        case SerialPortEvent.DSR:/*Data set ready，数据设备就绪*/
        case SerialPortEvent.RI:/*Ring indicator，响铃指示*/
        case SerialPortEvent.OUTPUT_BUFFER_EMPTY:/*Output buffer is empty，输出缓冲区清空*/
            break;
        case SerialPortEvent.DATA_AVAILABLE:/*Data available at the serial port，端口有可用数据。读到缓冲数组，输出到终端*/
            byte[] readBuffer = new byte[20];
            char[] readChar = new char[20];
            String readStr="";
            int numBytes=0;
            try {
                while (inputStream.available() > 0) {
                    numBytes= inputStream.read(readBuffer);
                }
                for(int iii=0;iii<numBytes;iii++){   
                    readStr=readStr + Byte.toString(readBuffer[iii]);                  
                }                     
                System.out.println(readStr.length());
                System.out.println(readStr);
            } catch (IOException e) {}                  
            break;            
        }
    }
}
