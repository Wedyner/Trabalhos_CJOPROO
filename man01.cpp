#include <raylib.h>
#include <string>

int main() {
    // Configuração inicial da janela
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Ping Pong WM");
    
    // Configuração do jogo
    const int paddleWidth = 15;
    const int paddleHeight = 100;
    const int ballSize = 15;
    
    // Posições iniciais
    Vector2 player1Pos = { 20, screenHeight/2 - paddleHeight/2 };
    Vector2 player2Pos = { screenWidth - 20 - paddleWidth, screenHeight/2 - paddleHeight/2 };
    Vector2 ballPos = { screenWidth/2, screenHeight/2 };
    Vector2 ballSpeed = { 5, 5 };
    
    // Placar
    int player1Score = 0;
    int player2Score = 0;
    
    // Controles
    float player1Speed = 0;
    float player2Speed = 0;
    const float paddleSpeed = 8;
    
    SetTargetFPS(60);
    
    // Loop principal do jogo
    while (!WindowShouldClose()) {
        // Atualização
        // Controles do jogador 1 (W/S)
        if (IsKeyDown(KEY_W)) player1Speed = -paddleSpeed;
        else if (IsKeyDown(KEY_S)) player1Speed = paddleSpeed;
        else player1Speed = 0;
        
        // Controles do jogador 2 (Cima/Baixo)
        if (IsKeyDown(KEY_UP)) player2Speed = -paddleSpeed;
        else if (IsKeyDown(KEY_DOWN)) player2Speed = paddleSpeed;
        else player2Speed = 0;
        
        // Movimentação das raquetes
        player1Pos.y += player1Speed;
        player2Pos.y += player2Speed;
        
        // Limitar raquetes dentro da tela
        if (player1Pos.y < 0) player1Pos.y = 0;
        if (player1Pos.y > screenHeight - paddleHeight) player1Pos.y = screenHeight - paddleHeight;
        if (player2Pos.y < 0) player2Pos.y = 0;
        if (player2Pos.y > screenHeight - paddleHeight) player2Pos.y = screenHeight - paddleHeight;
        
        // Movimentação da bola
        ballPos.x += ballSpeed.x;
        ballPos.y += ballSpeed.y;
        
        // Colisão com as bordas superior e inferior
        if (ballPos.y < 0 || ballPos.y > screenHeight - ballSize) {
            ballSpeed.y *= -1;
        }
        
        // Colisão com as raquetes
        if (CheckCollisionCircleRec(ballPos, ballSize/2, 
            { player1Pos.x, player1Pos.y, paddleWidth, paddleHeight }) && ballSpeed.x < 0) {
            ballSpeed.x *= -1.1f; // Aumenta a velocidade após rebater
        }
        
        if (CheckCollisionCircleRec(ballPos, ballSize/2, 
            { player2Pos.x, player2Pos.y, paddleWidth, paddleHeight }) && ballSpeed.x > 0) {
            ballSpeed.x *= -1.1f; // Aumenta a velocidade após rebater
        }
        
        // Verificar se a bola saiu da tela (ponto)
        if (ballPos.x < 0) {
            player2Score++;
            ballPos = { screenWidth/2, screenHeight/2 };
            ballSpeed = { -5, 5 };
        }
        
        if (ballPos.x > screenWidth) {
            player1Score++;
            ballPos = { screenWidth/2, screenHeight/2 };
            ballSpeed = { 5, 5 };
        }
        
        // Desenho
        BeginDrawing();
            ClearBackground(BLACK);
            
            // Desenhar a mesa (linha central e bordas)
            DrawRectangle(screenWidth/2 - 1, 0, 2, screenHeight, DARKGRAY);
            DrawRectangleLines(0, 0, screenWidth, screenHeight, WHITE);
            
            // Desenhar as iniciais WM no centro
            DrawText("WM", screenWidth/2 - MeasureText("WM", 40)/2, screenHeight/2 - 20, 40, LIGHTGRAY);
            
            // Desenhar as raquetes
            DrawRectangleRec({ player1Pos.x, player1Pos.y, paddleWidth, paddleHeight }, WHITE);
            DrawRectangleRec({ player2Pos.x, player2Pos.y, paddleWidth, paddleHeight }, WHITE);
            
            // Desenhar a bola
            DrawCircleV(ballPos, ballSize/2, WHITE);
            
            // Desenhar o placar
            DrawText(TextFormat("%i", player1Score), screenWidth/4, 20, 40, WHITE);
            DrawText(TextFormat("%i", player2Score), 3*screenWidth/4 - MeasureText(TextFormat("%i", player2Score), 40), 20, 40, WHITE);
            
            // Instruções
            DrawText("Jogador 1: W/S", 10, 10, 20, GRAY);
            DrawText("Jogador 2: Setas", screenWidth - MeasureText("Jogador 2: Setas", 20) - 10, 10, 20, GRAY);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}