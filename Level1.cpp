#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"

void Level1::Load()
{
    sprites = new SpriteSheet(L"SpriteSheet.png", gfx, 90, 90);

    bool isWhite = true;

    if (isWhite) {
        boardArr = {
                    {10,11,12,9,8,12,11,10},
                    {13,13,13,13,13,13,13,13},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {7,7,7,7,7,7,7,7},
                    {4,5,6,3,2,6,5,4}

        };
    }
    else {
        boardArr = {
                    {4,5,6,3,2,6,5,4},
                    {7,7,7,7,7,7,7,7},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {13,13,13,13,13,13,13,13},
                    {10,11,12,9,8,12,11,10}
        };
    }
}

void Level1::Unload()
{
    delete sprites;
}

void Level1::EventProcess(UINT uMsg, HWND hwnd, double timeDelta)
{

    lochwnd = hwnd;

    if (uMsg == WM_LBUTTONDOWN) {

        GetCursorPos(&p);
        ScreenToClient(lochwnd, &p);

        int x = int(p.x / 90);
        int y = int(p.y / 90);

        if (x < 8 && y < 8) {
            if (!grabbed) {
                prevpos = { x, y };
                grabbed = boardArr[y][x];
                boardArr[y][x] = 0;
                wrong = false;
            }
            else {
                std::vector<std::vector<int>> preboardArr = boardArr;
                std::vector<std::vector<int>> postboardArr = boardArr;
                preboardArr[prevpos[1]][prevpos[0]] = grabbed;
                if (truthy(prevpos, { x, y }, preboardArr, move, &enpassant, &boardArr)) {
                    postboardArr[y][x] = grabbed;
                    if (inchecked(postboardArr, move))
                    {
                        MessageBoxA(lochwnd, "You Are Currently In Check", "Checked", MB_OK);
                        boardArr[prevpos[1]][prevpos[0]] = grabbed;
                        grabbed = 0;
                        wrongpos = { x, y };
                        wrong = true;
                        boardArr = preboardArr;
                    }
                    else
                    {
                        boardArr[y][x] = grabbed;
                        grabbed = 0;
                        lochwnd = hwnd;
                        move++;
                    }

                }
                else {
                    boardArr[prevpos[1]][prevpos[0]] = grabbed;
                    grabbed = 0;
                    wrongpos = { x, y };
                    wrong = true;
                }
            }
        }
    }
}

void Level1::Update(double timeDelta)
{
    if (grabbed) {
        GetCursorPos(&p);
        ScreenToClient(lochwnd, &p);

    }
    for (uint16_t x = 0; x < 8; x++)
    {
        if (boardArr[0][x] == 7)
            boardArr[0][x] = 3;
    }
    for (uint16_t x = 0; x < 8; x++)
    {
        if (boardArr[7][x] == 13)
            boardArr[7][x] = 9;
    }
}

void Level1::Render()
{
    gfx->ClearScreen(1.0f, 1.0f, 1.0f);

    for (uint16_t x = 0; x < 8; x++)
    {
        for (uint16_t y = 0; y < 8; y++)
        {
            sprites->Draw((x % 2 + y % 2) % 2, x * 90, y * 90);

            if (boardArr[y][x] != 0)
                sprites->Draw(boardArr[y][x], x * 90, y * 90);

        }
    }
    if (grabbed != 0) {
        gfx->FillRect(prevpos[0] * 90, prevpos[1] * 90, 90, 90, 1.0f, 1.0f, 0.20f, 0.5f);
        sprites->Draw(grabbed, p.x - 45, p.y - 45);
    }
    if (wrong)
        gfx->FillRect(wrongpos[0] * 90, wrongpos[1] * 90, 90, 90, 1.0f, 0.20f, 0.20f, 0.5f);
}