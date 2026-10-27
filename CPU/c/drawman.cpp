// #include "../h/raylib.h"
// #include <stdlib.h>
// #include <math.h>
// Color GetRGB(unsigned char element) {
//     //четыре битса в инте яркость, р, г, б
//     //это хуйня будем лучше делать RRRGGGBB
//     unsigned char r = ((element >> 5) & 0x07) * 36; // 36 = 255 / 7
//     unsigned char g = ((element >> 2) & 0x07) * 36;
//     unsigned char b = (element & 0x03) * 85;        // 85 = 255 / 3
//     return {r,g,b,255};
// }
//
// int Drawman(unsigned char *arr, size_t arr_length) {
//     int side = (int)sqrt(arr_length);
//
//     int pixel_scale = 1;
//
//
//     int window_width = side * pixel_scale;
//     int window_height = side * pixel_scale;
//
//     InitWindow(window_width, window_height, "pick me");
//     SetTargetFPS(60);
//
//     while (!WindowShouldClose()) {
//         BeginDrawing();
//         ClearBackground(BLACK);
//

//         for (int y = 0; y < side; y++) {
//             for (int x = 0; x < side; x++) {
//                 int index = y * side + x;
//                 unsigned char element = arr[index];
//
//                 Color color = GetRGB(element);
//
//                 DrawRectangle(
//                     x * pixel_scale,
//                     y * pixel_scale,
//                     pixel_scale,
//                     pixel_scale,
//                     color
//                 );
//             }
//         }
//
//         EndDrawing();
//     }
//
//     CloseWindow();
//     return 0;
// }

