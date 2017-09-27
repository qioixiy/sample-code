// http://basiccoder.com/play-wav-using-gst.html

#include <stdio.h>
#include <assert.h>
#include <gst/gst.h>

static void
add_pad (GstElement *element , GstPad *pad , gpointer data){

    gchar *name;
    GstElement *sink = (GstElement*)data;

    name = gst_pad_get_name(pad);
    gst_element_link_pads(element , name , sink , "sink");
    g_free(name);
}

static gboolean
bus_watch(GstBus *bus , GstMessage *msg , gpointer data)
{
    GMainLoop *loop = (GMainLoop *) data;
    switch (GST_MESSAGE_TYPE(msg))
    {
    case GST_MESSAGE_EOS:
        g_print("End of stream\n");
        g_main_loop_quit(loop);
        break;
    case GST_MESSAGE_ERROR:
    {
        gchar *debug;
        GError *error;
        gst_message_parse_error(msg,&error,&debug);
        g_free(debug);
        g_printerr("ERROR:%s\n",error->message);
        g_error_free(error);
        g_main_loop_quit(loop);

        break;
    }
    default:
        break;
    }
    return TRUE;
}

void
play_file(const char *filename){

    GMainLoop *loop;
    GstElement *pipeline;
    GstBus *bus;
    GstElement *source , *parser , *sink;

    loop = g_main_loop_new(NULL , TRUE);

    pipeline = gst_pipeline_new("audio-player");

    source = gst_element_factory_make("filesrc" , "source");
    parser = gst_element_factory_make("wavparse" , "parser");
    sink = gst_element_factory_make("alsasink" , "output");

    g_object_set(G_OBJECT(source) , "location"
                 , filename , NULL);

    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_watch(bus , bus_watch , loop);
    g_object_unref(bus);

    gst_bin_add_many(GST_BIN(pipeline)
                     , source , parser , sink , NULL);

    g_signal_connect(parser
                     , "pad-added" , G_CALLBACK(add_pad) , sink);

    if(! gst_element_link(source , parser)){
        g_warning("linke source to parser failed");
    }

    gst_element_set_state(pipeline , GST_STATE_PLAYING);
    printf("Start playing...\n");
    g_main_loop_run(loop);
    printf("Playing stopped!!!\n");
    gst_element_set_state(pipeline , GST_STATE_NULL);
    g_object_unref(pipeline);
}

void
record_file(const char *filename){

    GMainLoop *loop;
    GstElement *pipeline;
    GstBus *bus;
    GstElement *source , *parser , *sink;

    loop = g_main_loop_new(NULL , TRUE);

    pipeline = gst_pipeline_new("wav-player");

    source = gst_element_factory_make("pulsesrc" , "source");
    g_object_set(G_OBJECT(source), "device", "alsa_input.multicapture", NULL);
    parser = gst_element_factory_make("wavenc" , "parser");
    sink = gst_element_factory_make("filesink" , "sink");
    printf("%s\n", filename);
    g_object_set(G_OBJECT(sink) , "location"
                 , filename , NULL);

    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_watch(bus , bus_watch , loop);
    g_object_unref(bus);

    gst_bin_add_many(GST_BIN(pipeline)
                     , source , parser , sink , NULL);

    g_signal_connect(parser
                     , "pad-added" , G_CALLBACK(add_pad) , sink);

    if(! gst_element_link_many(source , parser, sink, NULL)){
        g_warning("linke source to parser failed");
    }

    gst_element_set_state(pipeline , GST_STATE_PLAYING);
    printf("Start recording...\n");
    g_main_loop_run(loop);
    printf("Playing stopped!!!\n");
    gst_element_set_state(pipeline , GST_STATE_NULL);
    g_object_unref(pipeline);
}

/* http://www.cnblogs.com/phinecos/archive/2009/06/07/1498166.html */
/* mad plugins in gstreamer1.0-plugins-ugly */
int mp3_player(int argc,char *argv[])
{
    GMainLoop *loop;
    GstElement *pipeline,*source,*decoder,*sink;
    GstBus *bus;

    loop = g_main_loop_new(NULL,FALSE);

    if(argc != 2)
    {
        g_printerr("Usage:%s <mp3 filename>\n",argv[0]);
        return -1;
    }

    pipeline = gst_pipeline_new("audio-player");
    source = gst_element_factory_make("filesrc","file-source");
    decoder = gst_element_factory_make("mad","mad-decoder");
    sink = gst_element_factory_make("autoaudiosink","audio-output");

    if(!pipeline||!source||!decoder||!sink){
        g_printerr("One element could not be created.Exiting.\n");
        return -1;
    }
    //设置 source的location 参数。即 文件地址.
    g_object_set(G_OBJECT(source),"location",argv[1],NULL);
    //得到 管道的消息总线
    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    //添加消息监视器
    gst_bus_add_watch(bus,bus_watch,loop);
    gst_object_unref(bus);
    //把组件添加到管道中.管道是一个特殊的组件，可以更好的让数据流动
    gst_bin_add_many(GST_BIN(pipeline),source,decoder,sink,NULL);
    //依次连接组件
    gst_element_link_many(source,decoder,sink,NULL);
    //开始播放
    gst_element_set_state(pipeline,GST_STATE_PLAYING);
    g_print("Running\n");
    //开始循环
    g_main_loop_run(loop);
    g_print("Returned,stopping playback\n");
    gst_element_set_state(pipeline,GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(pipeline));
    return 0;
}

void
show_banner()
{
    const gchar *nano_str;
    guint major, minor, micro, nano;
    gst_version (&major, &minor, &micro, &nano);

    if (nano == 1)
        nano_str = "(CVS)";
    else if (nano == 2)
        nano_str = "(Prerelease)";
    else
        nano_str = "";
    printf ("This program is linked against GStreamer %d.%d.%d %s\n",
            major, minor, micro, nano_str);
}

int
main(int argc , char *argv[]){

    show_banner();
    gst_init(&argc , &argv);

    //play_file(argv[1]);
    //record_file(argv[1]);
    mp3_player(argc, argv);

    return 0;
}
