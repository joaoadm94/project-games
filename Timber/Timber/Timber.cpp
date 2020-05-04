// HelloSFML.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.

// Inclusão de bibliotecas importantes aqui
#include <iostream>
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
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    /*
    Sprite spriteClouds[5];
    bool cloudActive[5];
    float cloudSpeed[5];
    for (int i = 0; i < 5; i++) {
        spriteClouds[i].setTexture(textureCloud);
        spriteClouds[i].setPosition(0, i * 160 * scale);
        spriteClouds[i].setScale(scale, scale);
        cloudActive[i] = false;
        cloudSpeed[i] = 0.0f;
    }*/

    Sprite spriteCloud1;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud1.setPosition(0, 0);
    spriteCloud1.setScale(scale, scale);
    bool cloud1Active = false;
    float cloud1Speed = 0.0f;

    Sprite spriteCloud2;
    spriteCloud2.setTexture(textureCloud);
    spriteCloud2.setPosition(0, 160 * scale);
    spriteCloud2.setScale(scale, scale);
    bool cloud2Active = false;
    float cloud2Speed = 0.0f;

    Sprite spriteCloud3;
    spriteCloud3.setTexture(textureCloud);
    spriteCloud3.setPosition(0, 320 * scale);
    spriteCloud3.setScale(scale, scale);
    bool cloud3Active = false;
    float cloud3Speed = 0.0f;

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

    // Posicionando os textos
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 * scale / 2.0f, 1080 * scale/ 2.0f);
    textRect = scoreText.getLocalBounds();
    scoreText.setOrigin(textRect.left + textRect.width, textRect.top);
    scoreText.setPosition(1900 * scale, 20 * scale);

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
            // Nuvem 1
            if (!cloud1Active) {
                // Determina velocidade da nuvem 1
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);
                // Determina altura da nuvem 1
                srand((int)time(0) * 10);
                float height = ((rand() % 150)) * scale;
                spriteCloud1.setPosition(-250 * scale, height);
                cloud1Active = true;
            }
            else {
                spriteCloud1.setPosition(
                    spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
                    spriteCloud1.getPosition().y);
                if (spriteCloud1.getPosition().x > 1920 * scale) {
                    cloud1Active = false;
                }
            }
            // Nuvem 2
            if (!cloud2Active) {
                // Determina velocidade da nuvem 2
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);
                // Determina altura da nuvem 1
                srand((int)time(0) * 10);
                float height = (rand() % 300) - 150;
                spriteCloud2.setPosition(-250 * scale, height);
                cloud2Active = true;
            }
            else {
                spriteCloud2.setPosition(
                    spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
                    spriteCloud2.getPosition().y);
                if (spriteCloud2.getPosition().x > 1920 * scale) {
                    cloud2Active = false;
                }
            }
            // Nuvem 3
            if (!cloud3Active) {
                // Determina velocidade da nuvem 2
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);
                // Determina altura da nuvem 1
                srand((int)time(0) * 30);
                float height = ((rand() % 450) - 150) * scale;
                spriteCloud3.setPosition(-250 * scale, height);
                cloud3Active = true;
            }
            else {
                spriteCloud3.setPosition(
                    spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
                    spriteCloud3.getPosition().y);
                if (spriteCloud3.getPosition().x > 1920 *  scale) {
                    cloud3Active = false;
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
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(timeBar);
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
