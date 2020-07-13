// HelloSFML.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.

// Inclusão de bibliotecas importantes aqui
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

// Namespace do SFML
using namespace sf;
enum class Side {LEFT, RIGHT, NONE};
int branchLeftX, branchRightX;

void updateBranches(Sprite sprites[], Side sides[], int branchAmount, int seed) {
    // Descer cada galho em um nível
    for (int i = branchAmount - 1; i > 0; i--) {
        sides[i] = sides[i - 1];
    }
    // Adicionar um novo galho no topo da árvore
    srand((int)time(0) + seed);
    int treeSideRand = (rand() % 5);
    switch (treeSideRand) {
        case 0:
            sides[0] = Side::LEFT;
            break;
        case 1:
            sides[0] = Side::RIGHT;
            break;
        default:
            sides[0] = Side::NONE;
    }
    for (int i = 0; i < branchAmount; i++) {
        if (sides[i] == Side::LEFT) {
            sprites[i].setRotation(180);
            sprites[i].setPosition(branchLeftX, sprites[i].getPosition().y);
        }
        else if (sides[i] == Side::RIGHT) {
            sprites[i].setRotation(0);
            sprites[i].setPosition(branchRightX, sprites[i].getPosition().y);
        }
        else {
            sprites[i].setPosition(-500, sprites[i].getPosition().y);
        }
    }
}

int main()
{
    // Criando objeto de modo de vídeo
    int desktopWidth = VideoMode::getDesktopMode().width;
    int desktopHeight = VideoMode::getDesktopMode().height;
    float scale = (float) desktopWidth / 1920.f;
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
    spriteTree.setScale(scale, scale);
    int spriteTreeWidth = spriteTree.getGlobalBounds().width;
    int spriteTreeHeight = spriteTree.getGlobalBounds().height;
    spriteTree.setPosition((desktopWidth - spriteTreeWidth)/2, 0);
    int spriteTreeLeft = spriteTree.getGlobalBounds().left;


    // Configurações da abelha
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(-1000, 800 * scale);
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
        spriteCloud[i].setPosition(-1000, 160 * scale * i);
        spriteCloud[i].setScale(scale, scale);
        cloudActive[i] = false;
        cloudSpeed[i] = 0.0f;
    }

    // Configurações para o lenhador
    Texture textureLumberjack;
    textureLumberjack.loadFromFile("graphics/player.png");
    Side sideLumberjack = Side::LEFT;
    Sprite spriteLumberjack;
    spriteLumberjack.setTexture(textureLumberjack);
    spriteLumberjack.setScale(scale, scale);
    int spriteLumberjackWidth = spriteLumberjack.getGlobalBounds().width;
    int spriteLumberjackHeight = spriteLumberjack.getGlobalBounds().height;
    int spriteLumberjackLeftX = spriteTreeLeft - spriteLumberjackWidth;
    int spriteLumberjackRightX = spriteTreeLeft + spriteTreeWidth;
    int spriteLumberjackY = spriteTreeHeight - spriteLumberjackHeight;
    spriteLumberjack.setPosition(spriteLumberjackLeftX, spriteLumberjackY);

    // Configurações para os galhos
    const int BRANCH_AMOUNT = 5;
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");
    int branchSpace;
    branchSpace = spriteTreeHeight - spriteLumberjackHeight/2;
    Side sidesBranch[BRANCH_AMOUNT];
    Sprite spriteBranches[BRANCH_AMOUNT];
    spriteBranches[0].setTexture(textureBranch);
    spriteBranches[0].setScale(scale, scale);
    int spriteBranchWidth = spriteBranches[0].getGlobalBounds().width;
    int spriteBranchHeight = spriteBranches[0].getGlobalBounds().height;

    // Atribui as configuracoes iniciais para os galhos
    // A altura dos galhos e calculada dividindo o espaco disponivel
    // na arvore pela quantidade de galhos, sendo o galho[0] o mais alto
    // e o galho[n] o mais baixo.
    for (int i = 0; i < BRANCH_AMOUNT; i++) {
        spriteBranches[i].setTexture(textureBranch);
        spriteBranches[i].setScale(scale, scale);
        spriteBranches[i].setPosition(-1000, i * (branchSpace/BRANCH_AMOUNT));
        spriteBranches[i].setOrigin(spriteBranches[0].getLocalBounds().width/2, spriteBranches[0].getLocalBounds().height/2);
        sidesBranch[i] = Side::NONE;
    }
    sidesBranch[0] = Side::LEFT;
    sidesBranch[1] = Side::RIGHT;
    sidesBranch[2] = Side::RIGHT;
    branchLeftX = spriteTreeLeft - (spriteBranchWidth/2);
    branchRightX = spriteTreeLeft + spriteTreeWidth + (spriteBranchWidth/2);
    updateBranches(spriteBranches, sidesBranch, BRANCH_AMOUNT, 0);

    // Configurações para o machado
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    int spriteAxeLeftX = spriteLumberjackLeftX + (spriteLumberjackWidth / 2);
    int spriteAxeRightX = spriteTreeLeft + 3*(spriteTreeWidth/4);
    int spriteAxeY = spriteLumberjackY + (spriteLumberjackHeight / 2);
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setScale(scale, scale);
    spriteAxe.setPosition(-1000, spriteAxeY);

    // Configurações para a lápide
    Texture textureRip;
    textureRip.loadFromFile("graphics/rip.png");
    Sprite spriteRip;
    spriteRip.setTexture(textureRip);
    spriteRip.setScale(scale, scale);
    spriteRip.setOrigin(0, spriteRip.getGlobalBounds().height);
    spriteRip.setPosition(-1000, spriteTreeHeight - 20);

    //Configurações para a tora
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setScale(scale, scale);
    int spriteLogHeight = spriteLog.getGlobalBounds().height;
    spriteLog.setPosition(spriteTreeLeft, spriteTreeHeight - spriteLogHeight);
 
    Time elapsed;

    // Inicializa número aleatório
    int number = (rand() % 100);

    // Variável para score
    int gameScore = 0;

    // Variável pra controle de tempo
    Clock clock;
    Clock updateClock;

    // Barra de tempo
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth * scale, timeBarHeight * scale));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(((1920 / 2) - timeBarStartWidth / 2) * scale, 980 * scale);
 
    Time gameTimeTotal;
    const float totalTime = 5.0f;
    float timeRemaining = 5.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
 
    // Variável de pausa
    bool paused = true;
    // Variável de hit do jogador
    bool hit = false;
    // Variável para determinar abertura para input
    bool acceptInput = true;

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
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased && !paused) {
                acceptInput = true;
                spriteAxe.setPosition(-500, spriteAxeY);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            gameScore = 0;
            timeRemaining = 5.0f;
        }
        if (acceptInput) {
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                sideLumberjack = Side::LEFT;
                gameScore++;
                timeRemaining += (2 / gameScore) + .15;
                if (timeRemaining >= 5.0f) {
                    timeRemaining = 5.0f;
                }
                acceptInput = false;
                hit = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                sideLumberjack = Side::RIGHT;
                gameScore++;
                timeRemaining += (2 / gameScore) + .15;
                if (timeRemaining >= 5.0f) {
                    timeRemaining = 5.0f;
                }
                acceptInput = false;
                hit = true;
            }
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

            if (hit && sideLumberjack == sidesBranch[BRANCH_AMOUNT - 1]) {
                paused = true;
            }
            
            // Atualiza a contagem de tempo
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining * scale, timeBarHeight * scale));
            
            // Se o tempo esgotar
            if (timeRemaining <= 0.0f) {
                paused = true;
                messageText.setString("Sem tempo, irmao!");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 * scale / 2.0f, 1080 * scale / 2.0f);
            }
            
            // Atualiza posicao do jogador
            if (hit) {
                if (sideLumberjack == Side::LEFT) {
                    spriteLumberjack.setPosition(spriteLumberjackLeftX, spriteLumberjackY);
                    spriteAxe.setPosition(spriteAxeLeftX, spriteAxeY);
                    updateBranches(spriteBranches, sidesBranch, BRANCH_AMOUNT, gameScore);
                    hit = false;
                } 
                else {
                    spriteLumberjack.setPosition(spriteLumberjackRightX, spriteLumberjackY);
                    spriteAxe.setPosition(spriteAxeRightX, spriteAxeY);
                    updateBranches(spriteBranches, sidesBranch, BRANCH_AMOUNT, gameScore);
                    hit = false;
                }
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
        for (int i = 0; i < BRANCH_AMOUNT; i++) {
            window.draw(spriteBranches[i]);
        }
        window.draw(spriteLumberjack);
        window.draw(spriteRip);
        window.draw(spriteLog);
        window.draw(spriteAxe);
        window.draw(timeBar);
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
