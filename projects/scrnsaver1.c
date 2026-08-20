// 屏保变幻线
// 编译： gcc -o xxx.scr xxx.c -lgdi32 -mwindows
// 放到 C:\Windows\System32 或 C:\Windows\SysWOW64
//        然后在屏幕保护设置中选择它。

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINES       15       // 折线条数
#define MAX_POINTS      4       // 每条折线的顶点数
#define TIMER_ID        1
#define TIMER_INTERVAL  20      // 定时器间隔(ms)

// 屏幕保护模式
typedef enum {
    SSM_NONE,
    SSM_SAVER,     // /s  全屏
    SSM_CONFIG,    // /c  配置
    SSM_PREVIEW    // /p  预览
} SSMode;

// 顶点结构
typedef struct {
    int   x, y;
    int   dx, dy;   // 速度
    COLORREF color;
} Vertex;

// 全局变量
static Vertex lines[MAX_LINES][MAX_POINTS]; // 每条线的顶点
static int screenW, screenH;
static SSMode mode = SSM_NONE;
static HWND hwndPreview = NULL;   // 预览父窗口句柄
static RECT previewRect;          // 预览区域

// 随机颜色
static COLORREF RandomColor() {
    return RGB(rand() % 256, rand() % 256, rand() % 256);
}

// 初始化顶点位置和速度（在全屏或预览区域内随机分布）
static void InitLines() {
    int w = screenW;
    int h = screenH;
    for (int i = 0; i < MAX_LINES; i++) {
        for (int j = 0; j < MAX_POINTS; j++) {
            lines[i][j].x = rand() % w;
            lines[i][j].y = rand() % h;
            lines[i][j].dx = (rand() % 5) + 2;  // 速度2..6
            lines[i][j].dy = (rand() % 5) + 2;
            if (rand() % 2) lines[i][j].dx = -lines[i][j].dx;
            if (rand() % 2) lines[i][j].dy = -lines[i][j].dy;
            lines[i][j].color = RandomColor();
        }
    }
}

// 更新顶点位置，碰到边界反弹并改变颜色
static void UpdateLines() {
    for (int i = 0; i < MAX_LINES; i++) {
        for (int j = 0; j < MAX_POINTS; j++) {
            Vertex *v = &lines[i][j];
            v->x += v->dx;
            v->y += v->dy;

            // 水平反弹
            if (v->x <= 0) {
                v->x = 0;
                v->dx = abs(v->dx);
                v->color = RandomColor();
            } else if (v->x >= screenW - 1) {
                v->x = screenW - 1;
                v->dx = -abs(v->dx);
                v->color = RandomColor();
            }

            // 垂直反弹
            if (v->y <= 0) {
                v->y = 0;
                v->dy = abs(v->dy);
                v->color = RandomColor();
            } else if (v->y >= screenH - 1) {
                v->y = screenH - 1;
                v->dy = -abs(v->dy);
                v->color = RandomColor();
            }
        }
    }
}

// 绘制所有折线
static void DrawLines(HDC hdc) {
    // 清屏（黑色背景）
    RECT rect = {0, 0, screenW, screenH};
    FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

    // 使用双缓冲避免闪烁（可选）
    for (int i = 0; i < MAX_LINES; i++) {
        // 选择画笔颜色为这条线的第一个顶点的颜色（或渐变）
        HPEN hPen = CreatePen(PS_SOLID, 2, lines[i][0].color);
        HPEN hOldPen = SelectObject(hdc, hPen);

        MoveToEx(hdc, lines[i][0].x, lines[i][0].y, NULL);
        for (int j = 1; j < MAX_POINTS; j++) {
            LineTo(hdc, lines[i][j].x, lines[i][j].y);
        }
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }
}

// 窗口过程
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            SetTimer(hwnd, TIMER_ID, TIMER_INTERVAL, NULL);
            return 0;

        case WM_TIMER:
            if (wParam == TIMER_ID) {
                UpdateLines();
                InvalidateRect(hwnd, NULL, FALSE); // 触发重绘
            }
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            DrawLines(hdc);
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_SIZE:
            // 更新绘图区域尺寸（预览窗口尺寸可能变化）
            if (mode == SSM_PREVIEW) {
                GetClientRect(hwnd, &previewRect);
                screenW = previewRect.right;
                screenH = previewRect.bottom;
            }
            return 0;

        case WM_DESTROY:
            KillTimer(hwnd, TIMER_ID);
            PostQuitMessage(0);
            return 0;

        // 任何按键或鼠标移动退出屏保（全屏模式）
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_MOUSEMOVE: {
            // 只在全屏模式下响应退出
            if (mode == SSM_SAVER) {
                // 鼠标移动阈值（首次移动时记录原始位置）
                static POINT lastMouse = {-1, -1};
                if (msg == WM_MOUSEMOVE) {
                    if (lastMouse.x == -1 && lastMouse.y == -1) {
                        lastMouse.x = LOWORD(lParam);
                        lastMouse.y = HIWORD(lParam);
                    } else {
                        int dx = abs(LOWORD(lParam) - lastMouse.x);
                        int dy = abs(HIWORD(lParam) - lastMouse.y);
                        if (dx > 3 || dy > 3)
                            PostQuitMessage(0);
                    }
                } else {
                    PostQuitMessage(0);
                }
            }
            return 0;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// 注册窗口类
static ATOM RegisterScreenSaverClass(HINSTANCE hInstance) {
    WNDCLASSEX wc = {0};
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = TEXT("MystifySaver");
    return RegisterClassEx(&wc);
}

// 创建全屏窗口
static HWND CreateFullscreenWindow(HINSTANCE hInstance) {
    screenW = GetSystemMetrics(SM_CXSCREEN);
    screenH = GetSystemMetrics(SM_CYSCREEN);
    return CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        TEXT("MystifySaver"), NULL,
        WS_POPUP | WS_VISIBLE,
        0, 0, screenW, screenH,
        NULL, NULL, hInstance, NULL);
}

// 创建预览子窗口
static HWND CreatePreviewWindow(HINSTANCE hInstance, HWND parent) {
    GetClientRect(parent, &previewRect);
    screenW = previewRect.right;
    screenH = previewRect.bottom;
    return CreateWindowEx(
        0,
        TEXT("MystifySaver"), NULL,
        WS_CHILD | WS_VISIBLE,
        0, 0, screenW, screenH,
        parent, NULL, hInstance, NULL);
}

// 解析命令行
static SSMode ParseCommandLine(LPSTR lpCmdLine, HWND *pPreviewWnd) {
    if (lpCmdLine == NULL || *lpCmdLine == '\0')
        return SSM_CONFIG;  // 默认打开配置（实际系统会传参数）

    // 复制一份以便分割
    char cmdline[256];
    strncpy(cmdline, lpCmdLine, sizeof(cmdline) - 1);
    cmdline[sizeof(cmdline) - 1] = '\0';

    char *token = strtok(cmdline, " \t");
    while (token != NULL) {
        if (token[0] == '/' || token[0] == '-') {
            switch (token[1]) {
                case 's': case 'S': return SSM_SAVER;
                case 'c': case 'C': return SSM_CONFIG;
                case 'p': case 'P': {
                    // 下一参数应该是预览窗口句柄
                    token = strtok(NULL, " \t");
                    if (token) {
                        *pPreviewWnd = (HWND)(INT_PTR)atoi(token);
                    }
                    return SSM_PREVIEW;
                }
            }
        }
        token = strtok(NULL, " \t");
    }
    return SSM_CONFIG;
}

// 程序入口
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)nCmdShow;

    // 初始化随机种子
    srand((unsigned)time(NULL));

    // 解析命令行
    HWND previewParent = NULL;
    mode = ParseCommandLine(lpCmdLine, &previewParent);

    // 如果是配置模式，可以弹出一个对话框，这里直接返回
    if (mode == SSM_CONFIG) {
        MessageBox(NULL, TEXT("Mystify 屏保 - 无配置选项"), TEXT("屏幕保护设置"),
                   MB_OK | MB_ICONINFORMATION);
        return 0;
    }

    // 注册窗口类
    if (!RegisterScreenSaverClass(hInstance))
        return 1;

    // 根据模式创建窗口
    HWND hwnd = NULL;
    if (mode == SSM_SAVER) {
        hwnd = CreateFullscreenWindow(hInstance);
    } else if (mode == SSM_PREVIEW) {
        if (previewParent == NULL) return 1;
        hwnd = CreatePreviewWindow(hInstance, previewParent);
    }
    if (hwnd == NULL) return 1;

    // 初始化线条位置
    InitLines();

    // 设置光标隐藏（全屏）
    if (mode == SSM_SAVER)
        ShowCursor(FALSE);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 恢复光标
    if (mode == SSM_SAVER)
        ShowCursor(TRUE);

    return (int)msg.wParam;
}