// infinite_ring

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TIMER_ID        1
#define TIMER_INTERVAL  30

#define MAX_RINGS       40
#define RING_SPACING    18
#define COLOR_SPEED     0.05f

typedef enum { MODE_NONE, MODE_SAVER, MODE_CONFIG, MODE_PREVIEW } SaverMode;

static int screenW, screenH;
static SaverMode mode = MODE_NONE;
static HWND hwndPreview = NULL;
static float phase = 0.0f;
static float hue = 0.0f;

static COLORREF HSVtoRGB(float h) {
    float r, g, b;
    int i = (int)(h * 6.0f);
    float f = h * 6.0f - i;
    float q = 1.0f - f;
    switch (i % 6) {
        case 0: r = 1.0f; g = f;     b = 0.0f; break;
        case 1: r = q;     g = 1.0f; b = 0.0f; break;
        case 2: r = 0.0f;  g = 1.0f; b = f;    break;
        case 3: r = 0.0f;  g = q;     b = 1.0f; break;
        case 4: r = f;     g = 0.0f;  b = 1.0f; break;
        default:r = 1.0f;  g = 0.0f;  b = q;    break;
    }
    return RGB((int)(r * 255), (int)(g * 255), (int)(b * 255));
}

static void DrawTunnel(HDC hdc) {
    RECT rc = {0, 0, screenW, screenH};
    FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));

    int cx = screenW / 2;
    int cy = screenH / 2;
    int maxRadius = (int)(sqrtf((float)(screenW*screenW + screenH*screenH)) / 2.0f) + 50;

    for (int i = 0; i < MAX_RINGS; i++) {
        float depth = (phase + (float)i / MAX_RINGS) - floorf(phase + (float)i / MAX_RINGS);
        float scale = sqrtf(depth) * 0.9f + 0.05f;
        int r = (int)(maxRadius * scale);
        if (r <= 0) continue;

        float h = hue + depth * 0.8f;
        h = h - floorf(h);
        COLORREF color = HSVtoRGB(h);

        int alpha = (int)(255.0f * (1.0f - depth));
        int red   = (GetRValue(color) * alpha) >> 8;
        int green = (GetGValue(color) * alpha) >> 8;
        int blue  = (GetBValue(color) * alpha) >> 8;
        COLORREF finalColor = RGB(red, green, blue);

        HPEN hPen = CreatePen(PS_SOLID, 2, finalColor);
        HPEN hOldPen = SelectObject(hdc, hPen);
        HBRUSH hOldBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH));
        Ellipse(hdc, cx - r, cy - r, cx + r, cy + r);
        SelectObject(hdc, hOldPen);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hPen);
    }
}

static void UpdateTunnel() {
    phase += 0.012f;
    if (phase >= 1.0f) phase -= 1.0f;
    hue += COLOR_SPEED;
    if (hue >= 1.0f) hue -= 1.0f;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            SetTimer(hwnd, TIMER_ID, TIMER_INTERVAL, NULL);
            return 0;
        case WM_TIMER:
            if (wParam == TIMER_ID) {
                UpdateTunnel();
                InvalidateRect(hwnd, NULL, FALSE);
            }
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            DrawTunnel(hdc);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_SIZE:
            if (mode == MODE_PREVIEW) {
                RECT rect;
                GetClientRect(hwnd, &rect);
                screenW = rect.right;
                screenH = rect.bottom;
            }
            return 0;
        case WM_DESTROY:
            KillTimer(hwnd, TIMER_ID);
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_MOUSEMOVE: {
            if (mode == MODE_SAVER) {
                static POINT last = {-1, -1};
                if (msg == WM_MOUSEMOVE) {
                    if (last.x == -1 && last.y == -1) {
                        last.x = LOWORD(lParam);
                        last.y = HIWORD(lParam);
                    } else {
                        int dx = abs(LOWORD(lParam) - last.x);
                        int dy = abs(HIWORD(lParam) - last.y);
                        if (dx > 3 || dy > 3) PostQuitMessage(0);
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

// 重命名以避免API 冲突
static ATOM RegisterTunnelClass(HINSTANCE hInst) {
    WNDCLASSEX wc = {0};
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = TEXT("TunnelSaver");
    return RegisterClassEx(&wc);
}

static HWND CreateFullscreen(HINSTANCE hInst) {
    screenW = GetSystemMetrics(SM_CXSCREEN);
    screenH = GetSystemMetrics(SM_CYSCREEN);
    return CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        TEXT("TunnelSaver"), NULL,
        WS_POPUP | WS_VISIBLE,
        0, 0, screenW, screenH,
        NULL, NULL, hInst, NULL);
}

static HWND CreatePreview(HINSTANCE hInst, HWND parent) {
    RECT rect;
    GetClientRect(parent, &rect);
    screenW = rect.right;
    screenH = rect.bottom;
    return CreateWindowEx(
        0, TEXT("TunnelSaver"), NULL,
        WS_CHILD | WS_VISIBLE,
        0, 0, screenW, screenH,
        parent, NULL, hInst, NULL);
}

static SaverMode ParseCmd(LPSTR cmd, HWND *pPreview) {
    if (!cmd || !*cmd) return MODE_CONFIG;
    char buf[256];
    strncpy(buf, cmd, 255);
    buf[255] = '\0';
    char *tok = strtok(buf, " \t");
    while (tok) {
        if (tok[0] == '/' || tok[0] == '-') {
            switch (tok[1]) {
                case 's': case 'S': return MODE_SAVER;
                case 'c': case 'C': return MODE_CONFIG;
                case 'p': case 'P':
                    tok = strtok(NULL, " \t");
                    if (tok) *pPreview = (HWND)(INT_PTR)atoi(tok);
                    return MODE_PREVIEW;
            }
        }
        tok = strtok(NULL, " \t");
    }
    return MODE_CONFIG;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmdLine, int nShow) {
    (void)hPrev; (void)nShow;
    srand((unsigned)time(NULL));

    HWND previewWnd = NULL;
    mode = ParseCmd(cmdLine, &previewWnd);

    if (mode == MODE_CONFIG) {
        MessageBox(NULL, TEXT("无限隧道屏保 - 无配置选项"), TEXT("屏幕保护设置"),
                   MB_OK | MB_ICONINFORMATION);
        return 0;
    }

    if (!RegisterTunnelClass(hInst)) return 1;

    HWND hwnd = (mode == MODE_SAVER) ? CreateFullscreen(hInst) :
                                      CreatePreview(hInst, previewWnd);
    if (!hwnd) return 1;

    phase = (float)(rand() % 1000) / 1000.0f;
    hue = (float)(rand() % 1000) / 1000.0f;

    if (mode == MODE_SAVER) ShowCursor(FALSE);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (mode == MODE_SAVER) ShowCursor(TRUE);
    return (int)msg.wParam;
}