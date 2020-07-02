// HelloSFML.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.

// Inclusão de bibliotecas importantes aqui
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <sstream>

// Namespace do SFML
using namespace sf;

int main()
{
    // Criando objeto de modo de vídeo
    int desktopWidth = VideoMode::getDesktopMode().width;
    int desktopHeight = VideoMode::getDesktopMode().height;
    float scale = (float)desktopWidth / 1920.f;
    VideoMode vm(desktopWidth, desktopHeight);
    // Criar e abrir janela para o jogo
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
    // Textura e sprite para o background
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);
    spriteBackground.setScale(scale, scale);

    // Textura e sprite para a árvore
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810 * scale, 0);
    spriteTree.setScale(scale, scale);

    // Configurações da abelha
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800 * scale);
    spriteBee.setScale(scale, scale);
    bool beeActive = false;
    float beeSpeed = 0.0f;

    // Configurações das nuvens
    const int cloudsAmount = 3;
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    Sprite spriteCloud[cloudsAmount];
    bool cloudActive[cloudsAmount];
    float cloudSpeed[cloudsAmount];
    for (int i = 0; i < cloudsAmount; i++) {
        spriteCloud[i].setTexture(textureCloud);
        spriteCloud[i].setPosition(0, 160 * scale * i);
        spriteCloud[i].setScale(scale, scale);
        cloudActive[i] = false;
        cloudSpeed[i] = 0.0f;
    } 
    
    // Inicializa número aleatório
    int number = (rand() % 100);

    // Variável para score
    int gameScore = 0;

    // Variável pra controle de tempo
    Clock clock;

    // Barra de tempo
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth * scale, timeBarHeight * scale));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(((1920 / 2) - timeBarStartWidth / 2) * scale, 980 * scale);
 
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
 
    // Variável de pausa
    bool paused = true;

    // Fonte para o HUD
    Font mainFont;
    mainFont.loadFromFile("fonts/KOMIKAP_.ttf");

    // Variáveis para texto
    Text messageText;
    messageText.setFont(mainFont);
    messageText.setString("Aperte Enter para jogar!");
    messageText.setCharacterSize(75 * scale);
    messageText.setFillColor(Color::White);
    
    Text scoreText;
    scoreText.setFont(mainFont);
    scoreText.setString("Score = 0");
    scoreText.setCharacterSize(100 * scale);
    scoreText.setFillColor(Color::White);

    // Posiciona o texto de abertura
    FloatRect messageRect = messageText.getGlobalBounds();
    messageText.setOrigin(messageRect.left + (messageRect.width / 2.0f),
        messageRect.top + (messageRect.height / 2.0f));
    messageText.setPosition(desktopWidth / 2.0f, desktopHeight / 2.0f );

    // Posiciona texto do score
    float scoreWidthOffset = 0.65f;
    float scoreHeightOffset = 0.03f;
    scoreText.setPosition(desktopWidth * scoreWidthOffset, desktopHeight * scoreHeightOffset);
    

    while (window.isOpen()) {
        // *********************************************
        // RECEBE INPUTS DO JOGADOR
        // *********************************************
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            gameScore = 0;
            timeRemaining = 5;
        }

        // *********************************************
        // ATUALIZA A CENA
        // *********************************************
        // Animação da abelha sem checagem de framerate
        /*
        if (beeActive) {
            int posicaoAbelha = spriteBee.getPosition().x;
            if (posicaoAbelha >= 2000) {
                posicaoAbelha = 0;
            }
            else {
                posicaoAbelha++;
            }
            spriteBee.setPosition(posicaoAbelha, 800);
        }
        */

        if (!paused) {
            // Implementação considerando o framerate
            // Mede o tempo
            Time dt = clock.restart();
            gameScore++;

            // Atualiza a contagem de tempo
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f((timeBarWidthPerSecond * timeRemaining) * scale, timeBarHeight * scale));
            
            // Se o tempo esgotar
            if (timeRemaining <= 0.0f) {
                paused = true;
                messageText.setString("Sem tempo, irmao!");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 * scale / 2.0f, 1080 * scale / 2.0f);
            }

            // Se a abelha estiver desativada, posiciona a abelha
            if (!beeActive) {
                // Determina a velocidade da abelha
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 200;

                // Determina a altura da abelha
                srand((int)time(0) * 10);
                float height = ((rand() % 500) + 500) * scale;
                // Com essa posição, a abelha fica fora de quadro
                spriteBee.setPosition(1950 * scale, height);
                beeActive = true;
            } else {
                // Do contrário, move a abelha
                spriteBee.setPosition(
                    spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                    spriteBee.getPosition().y);
                // Se já tiver saído do quadro pela esquerda, reseta a abelha
                if (spriteBee.getPosition().x < (-100 * scale)) {
                    beeActive = false;
                }
            }

            // Animação das nuvens
            for (int i = 0; i < cloudsAmount; i++) {
                int j = i + 1;
                if (!cloudActive[i]) {
                    // Determina velocidade da nuvem
                    srand((int)time(0) * 10 * j); 
                    cloudSpeed[i] = (rand() % 200);
                    // Determina altura da nuvem
                    srand((int)time(0) * 10 * j);
                    float height = ((rand() % (150 * j)) - (150 * i)) * scale;
                    spriteCloud[i].setPosition(-250 * scale, height);
                    cloudActive[i] = true;
                }
                else {
                    spriteCloud[i].setPosition(
                        spriteCloud[i].getPosition().x + (cloudSpeed[i] * dt.asSeconds()),
                        spriteCloud[i].getPosition().y);
                    if (spriteCloud[i].getPosition().x > 1920 * scale) {
                        cloudActive[i] = false;
                    }
                }
            }
            // Atualiza a mensagem de score
            std::stringstream ss;
            ss << "Score = " << gameScore;
            scoreText.setString(ss.str());
            FloatRect textRect = scoreText.getLocalBounds();
            scoreText.setOrigin(textRect.left + textRect.width, textRect.top);
        }
        // *********************************************
        // DESENHA O FRAME
        // *********************************************
        // Limpa o último frame
        window.clear();
        // Desenha cada item da cena
        window.draw(spriteBackground);
        for (int i = 0; i < cloudsAmount; i++) {
            window.draw(spriteCloud[i]);
        }
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(scoreText);
        if (paused) {
            window.draw(messageText);
        }
        // Exibe o que foi desenhado
        window.display();
    }

    return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
