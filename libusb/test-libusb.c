// url:http://blog.sina.com.cn/s/blog_8a84e6d301015uh7.html
#include <stdio.h>
#include <string.h>
#include <usb.h>

#define IdVendor 0x0079       //这是我设备的厂商号
#define IdProduct 0x0006      //这是我设备的产品号，当你的usb设备接入电脑时，使用lsusb -v命令来查看设备信息，请看下面第三张图片中的0079:0006
//#define PrintDev

char enp_num[8],buf8[8],is_change=0;

//端点描述符
static void print_endpoint(struct usb_endpoint_descriptor *endpoint)
{
	printf("      bEndpointAddress: %xh\n", endpoint->bEndpointAddress);
	printf("      bmAttributes:     %xh\n", endpoint->bmAttributes);
	printf("      wMaxPacketSize:   %d\n", endpoint->wMaxPacketSize);
	printf("      bInterval:        %d\n", endpoint->bInterval);
	printf("      bRefresh:         %d\n", endpoint->bRefresh);
	printf("      bSynchAddress:    %d\n", endpoint->bSynchAddress);
}

static void print_altsetting(struct usb_interface_descriptor *interface)
{
	int i;

	printf("    bInterfaceNumber:   %d\n", interface->bInterfaceNumber);
	printf("    bAlternateSetting:  %d\n", interface->bAlternateSetting);
	printf("    bNumEndpoints:      %d\n", interface->bNumEndpoints);
	printf("    bInterfaceClass:    %d\n", interface->bInterfaceClass);
	printf("    bInterfaceSubClass: %d\n", interface->bInterfaceSubClass);
	printf("    bInterfaceProtocol: %d\n", interface->bInterfaceProtocol);
	printf("    iInterface:         %d\n", interface->iInterface);

	for (i = 0; i < interface->bNumEndpoints; i++)
		print_endpoint(&interface->endpoint[i]);
}

//显示设备所拥有的所有接口的描述符
static void print_interface(struct usb_interface *interface)
{
	int i;

	for (i = 0; i < interface->num_altsetting; i++)
		print_altsetting(&interface->altsetting[i]);
}

//配置描述符
static void print_configuration(struct usb_config_descriptor *config)
{
	int i;

	printf("  wTotalLength:         %d\n", config->wTotalLength);
	printf("  bNumInterfaces:       %d\n", config->bNumInterfaces);
	printf("  bConfigurationValue:  %d\n", config->bConfigurationValue);
	printf("  iConfiguration:       %d\n", config->iConfiguration);
	printf("  bmAttributes:         %xh\n", config->bmAttributes);
	printf("  MaxPower:             %d\n", config->MaxPower);

	for (i = 0; i < config->bNumInterfaces; i++)
		print_interface(&config->interface[i]);
}

static void print_device(struct usb_device *dev)
{
    //读取描述符
    int i;
    char description[256];
    snprintf(description, sizeof(description), "%x-%x", dev->descriptor.idVendor, dev->descriptor.idProduct);
    printf("Dev #%d: %s\n", dev->devnum,description);
    for (i = 0; i < dev->descriptor.bNumConfigurations; i++)
		print_configuration(&dev->config[i]);

}

//因为我的游戏设备属于HID类型，所以他与电脑通过中断端点进行数据传输。当摇杆位置变化或者按键按下时，读取设备中断端点值
static int read_interupt(struct usb_device *dev)
{
    usb_dev_handle *udev;
   
    char buf[256];
    int ret,i;
    udev=usb_open(dev);
   
    //#ifdef PrintDev
	//print_device(dev);
    //#endif
 
    //使用libusb驱动前必须使接口脱离linux内核驱动
    usb_detach_kernel_driver_np(udev,0);
    //操作libusb接口函数时需要声明接口
    usb_claim_interface(udev,0);
    //读中断端点1
    ret=usb_interrupt_read(udev,1,buf8,8,0x0a);
    //printf("%d\n",ret);
    usb_release_interface(udev,0);
    for(i=0;i<8;i++)
    {
        if(i==2)    //为了消除第二项不稳定因素
            continue;
        if(enp_num[i]!=buf8[i])
        {
            is_change=1;
            break;
        }
    }
   
    if(is_change==1)
    {
        is_change=0;
        for(i=0;i<8;i++)
        {
            enp_num[i]=buf8[i];
            printf("%d ",enp_num[i]);
                       
        }
        printf("\n");
    }
    if (udev)
        usb_close(udev);
    return 0;
}

int main(int argc, char *argv[])
{
    struct usb_bus *bus;
    struct usb_device *dev;
   
    usb_init();
    usb_find_busses();
    usb_find_devices();
   
    memset(enp_num,0,sizeof(enp_num));
    memset(buf8,0,sizeof(buf8));
    for (bus = usb_busses; bus; bus = bus->next) {       
		for (dev = bus->devices; dev; dev = dev->next)     
		{
			if((dev->descriptor.idVendor==IdVendor)&&(dev->descriptor.idProduct==IdProduct))
			{                                              
				while(1)
				{
					read_interupt(dev);
				}              
			}
		}
	}
	printf("*****************************\n");
  
	return 0;
}

//控制传输命令，通过控制端点(端点0)进行数据传输  
//renum=usb_control_msg(udev,0x80,USB_REQ_GET_DESCRIPTOR,
//0x0100,0,description,USB_DT_DEVICE_SIZE,0);
