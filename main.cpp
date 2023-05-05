#include "main.h"

using namespace std;

bool g_running = true;
// 信号处理函数
static void stopRunning(int exitCode)
{
    g_running = false;
}

// 为字符串中的"添加转义
char *escape_string(const char *str)
{
    char *escaped = (char *)malloc(strlen(str) * 6);
    if (escaped == NULL)
        return NULL;

    char *ptr = escaped;
    while (*str)
    {
        if (*str == '"')
        {
            *ptr++ = '\"';
        }
        else
        {
            *ptr++ = *str;
        }
        str++;
    }
    *ptr = '\0';

    return escaped;
}

const char *onTask(const char *uri, const char *aiType)
{
    if (0 == g_running)
    {
        cout << "The main program has quit" << endl;
    }
    int ret = -1;
    map<string, string> replyfield_string_map; // 存储消息字段
    string tempPicName(IOT_TO_PIC_KEY1);       // 临时存储图片名
    tempPicName += ".jpg";

    ret = getUrlPic(uri, tempPicName.c_str()); // 下载图片
    if (0 != ret)
    {
        exit(EXIT_FAILURE);
    }
    clock_t startTime = clock();
    vector<ret_rect> result = faceDetect(tempPicName.c_str()); // 人脸检测
    clock_t endTime = clock();
    double totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    cout << "Detect Time: " << totalTime << "s" << endl;
    cout << "result.num: " << result.size() << endl;
    // 保存检测结果
    replyfield_string_map[REPLY_KEY] = ret_rect_to_json(result);

    return escape_string(replyfield_string_map[REPLY_KEY].c_str());
}

int main()
{
    int ret;

    ret = logs_init(); // 初始化log
    if (0 != ret)
    {
        return -1;
    }
    faceDetect_init(0.5); // 人脸检测模型导入
    if (0 != ret)
    {
        return -1;
    }
    signal(SIGINT, stopRunning);
    const char *pszCapabilities[] = {"face_detect", "face_reg"};
    Init(onTask, pszCapabilities, 2); // 注册回调函数
    while (g_running)
    {
        pause();
    }
    system("rm *.jpg");
    return 0;
}
