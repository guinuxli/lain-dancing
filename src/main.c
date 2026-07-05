#include <raylib.h>

const int SCREEN_W = 1024;
const int SCREEN_H = 768;

int main() {

    InitWindow(SCREEN_W, SCREEN_H, "Lain");
    InitAudioDevice();
    
    Texture2D lainDancing = LoadTexture("assets/sprites/lain_dancing.png");
    Texture2D lainStanding = LoadTexture("assets/sprites/lain_stand.png");
    Music song = LoadMusicStream("assets/mus/song.ogg");

    PlayMusicStream(song);
    song.looping = true;

    // --- config PERSONAGEM ---
    const int frameCount = 8;
    const int frameWidth = lainDancing.width / frameCount;
    const int frameHeight = lainDancing.height;

    Rectangle lainDancingSource = {
        0.0f,
        0.0f,
        (float)frameWidth,
        (float)frameHeight
    };

    Vector2 lainDancingPosition = {
        (SCREEN_W - frameWidth) / 2.0f,
        (SCREEN_H - frameHeight) / 2.0f
    };

    const float lainDancingYOffset = 30;
    Vector2 lainDancingDrawPosition = {
        lainDancingPosition.x,
        lainDancingPosition.y - lainDancingYOffset
    };

    int currentFrame = 0;
    float timer = 0.0f;
    const float frameTime = 0.1; // 100ms por frame

    bool isDancing = false; // parado por padrão
    

    // --- config BACKGROUND ---
    Texture2D bgSheet = LoadTexture("assets/sprites/bg_sheet.png");

    const int bgFrameCount = 46;
    const int bgCols = 8;
    const int bgRows = 6;
    const int bgFrameWidth = bgSheet.width / bgCols;
    const int bgFrameHeight = bgSheet.height / bgRows;

    Rectangle bgSource = {
        0.0f,
        0.0f,
        (float)bgFrameWidth,
        (float)bgFrameHeight
    };

    int bgFrame = 0;
    float bgTimer = 0.0f;
    const float bgFrameTime = 1.0f / 24.0f;

    SetTargetFPS(60);

    // --- LOOP PRINCIPAL ---
    while(!WindowShouldClose()) {
        float dt = GetFrameTime();

        // input para trocar o sprite
        if(IsKeyPressed(KEY_SPACE)) {
            isDancing = !isDancing;

            if(isDancing) {
                currentFrame = 0;
                timer = 0.0f;
                lainDancingSource.x = 0.0f;
            }
        }

        bgTimer += dt;
        if (bgTimer >= bgFrameTime) {
            bgTimer -= bgFrameTime;
            bgFrame = (bgFrame + 1) % bgFrameCount;

            int col = bgFrame % bgCols;
            int row = bgFrame / bgCols;
            bgSource.x = (float)(col * bgFrameWidth);
            bgSource.y = (float)(row * bgFrameHeight);
        }

        // avança a animação de dança apenas
        // quando a variável é true
        if(isDancing) {
            timer += dt;
            if (timer >= frameTime) {
                timer -= frameTime;
                currentFrame = (currentFrame + 1) % frameCount;
                lainDancingSource.x = (float)(currentFrame * frameWidth);
            }
        }

        // update loop song
        UpdateMusicStream(song);

        BeginDrawing();

            // desenha o bg
            DrawTexturePro(
                bgSheet,
                bgSource,
                (Rectangle){0.0f, 0.0f, (float)SCREEN_W, (float)SCREEN_H},
                (Vector2){0.0f, 0.0f},
                0.0f,
                WHITE
            );
            
            // desenha a lain (dançando ou parada, dependendo do estado)
            // as duas usam lainDancingPosition, então não "pula" de lugar ao trocar
            if (isDancing) {
                DrawTextureRec(lainDancing, lainDancingSource, lainDancingDrawPosition, WHITE);
            } else {
                DrawTextureV(lainStanding, lainDancingPosition, WHITE);
            }


            DrawText("Press Space to make Lain Dance!", 350, 600, 22, BLACK);
        EndDrawing();
    }

    // --- Descarrecando dados da memória ---
    UnloadMusicStream(song);
    CloseAudioDevice();
    UnloadTexture(lainDancing);
    UnloadTexture(lainStanding);
    UnloadTexture(bgSheet);
    CloseWindow();

    return 0;
}
