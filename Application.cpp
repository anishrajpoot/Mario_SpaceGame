#include "Application.h"


#define Log(x) std::cout << x << std::endl


//******************************   VARIABLES HERE **********************************************


AudioManager mainMenuAudioManager;
AudioManager gameOverAudioManager;
AudioManager gameplayMenuAudioManager;

AudioManager star1AudioManager;
AudioManager star2AudioManager;
AudioManager star3AudioManager;


SDL_Texture* rockTexture;

Sprite obstacleA;
Sprite obstacleB;
Sprite obstacleC;
Sprite obstacleD;;
Sprite obstacleE;





long long unsigned int score = 0;
long long unsigned int starsCount = 0;
long long unsigned int highScore = 0;

Sprite spaceBackgroundA;
Sprite spaceBackgroundB;

Sprite star;
Sprite star2;
Sprite star3;
Sprite mainMenuBG;
Sprite gameOverBG;
Sprite scoreButtonBG;
Sprite starsButtonBG;



SDL_Texture* spaceTexture;
SDL_Texture* starTexture;
SDL_Texture* mainMenuBGTexture;
SDL_Texture* gameOverBGTexture;
SDL_Texture* buttonBGTexture;

std::fstream highScoreFile(HIGH_SCORE_FILE, std::ios::in | std::ios::out);

Font mainMenuFont;
Font font;

Text scoreText;
Text starsText;
Text highScoreText;


Text gameOverScoreText;


// Gameplay Layers
std::vector<Sprite> BackgroundLayer_Gameplay = { spaceBackgroundA,spaceBackgroundB };  // Background Layer  
std::vector<Sprite> ObstacleLayer_Gameplay;  // Layer Containing All The Obstacles
std::vector<Text> TextLayer_Gameplay = { scoreText, starsText };

LinkedList<Sprite> SpaceBackgroundsList;



// Tracks The Current Scene
int currentScene = SCENE_MAIN_MENU;

void initAllAudio()
{
    gameOverAudioManager.Initialize();
    mainMenuAudioManager.Initialize();
    gameplayMenuAudioManager.Initialize();
    star1AudioManager.Initialize();
    star2AudioManager.Initialize();
    star3AudioManager.Initialize();
}

void stopAllAudio()
{
    gameOverAudioManager.StopAudio();
    mainMenuAudioManager.StopAudio();
    star1AudioManager.StopAudio();
    star2AudioManager.StopAudio();
    star3AudioManager.StopAudio();
    gameplayMenuAudioManager.StopAudio();

}


void LoadScene(int sceneID)
{
    // Load The Main Menu Scene
    if (sceneID == SCENE_MAIN_MENU)
    {
        //stopAllAudio();
        //mainMenuAudioManager.PlayAudioAsync(MAIN_MENU_THEME,-1,true);
        currentScene = SCENE_MAIN_MENU;
    }

    // Load The Gameplay Scene
    else if (sceneID == SCENE_GAMEPLAY)
    {
        //stopAllAudio();
        //gameplayMenuAudioManager.PlayAudioAsync(GAMEPLAY_MENU_THEME,-1,true);
        currentScene = SCENE_GAMEPLAY;
    }

    // Load The GameOver Scene
    else if (sceneID == SCENE_GAME_OVER)
    {
       // stopAllAudio();
        //gameOverAudioManager.PlayAudioAsync(GAME_OVER_SOUND, 3000);
        currentScene = SCENE_GAME_OVER;
    }

    // Add Any Other Scenes (If Any)

    // If SceneID Doesnt Match
    else
    {
        Error::PrintExit("<SceneLoadError>", " No Such Scene With ID " + std::to_string(sceneID) + " Exists\n");
    }
}

// ************************************** END ***************************************************


void UpdateHighScore() {
    if (score > highScore) {
        highScore = score+1;
        std::cout << "New High Score: " << highScore << std::endl;

        highScoreFile.clear(); // Clear any flags
        highScoreFile.seekp(0); // Move to the beginning of the file
        if (!(highScoreFile << highScore)) {
            std::cerr << "Error writing high score to file" << std::endl;
        }
    }
}

// Game Related Functions
void OnCollisionWithObstacle()
{
    Print::RedLine("You Are Dead!!");
    std::cout << "Score : " << score+1 << std::endl;
    LoadScene(SCENE_GAME_OVER);

    UpdateHighScore();
}

void OnCollisionWithStar()
{   
    Print::YellowLine("You Collected Star!!");
    star.y = -1000;
    star.x = Random::Range(0, screenWidth*2);
    starsCount++;
    //star1AudioManager.PlayAudioAsync(STAR_COLLECT_SOUND, 200);
}
void OnCollisionWithStar2()
{
    
    Print::YellowLine("You Collected Star 2!!");
    star2.y = -1000;
    star2.x = Random::Range(0, screenWidth * 2);
    starsCount++;
    //star2AudioManager.PlayAudioAsync(STAR_COLLECT_SOUND, 200);
}
void OnCollisionWithStar3()
{
    Print::YellowLine("You Collected Star 3!!");
    star3.y = -1000;
    star3.x = Random::Range(0, screenWidth * 2);
    starsCount++;
    //star3AudioManager.PlayAudioAsync(STAR_COLLECT_SOUND, 200);
}






// Constructor
Application::Application()
{

    // Create a resizable window
    m_window = SDL_CreateWindow(gameName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_RESIZABLE);

    // If window creation fails
    if (!m_window)
    {
        Error::Print("Error! Failed To Create The Window...", SDL_GetError());
        return;
    }

    // Create the Renderer object
    m_renderer = new Renderer(m_window);
    if (!m_renderer->Init())
    {
        Error::Print("Error! Renderer initialization failed!", SDL_GetError());
        return;
    }

    // Initialize The SDL TTF Font Library
    if (TTF_Init() == -1) {
        Error::Print("Failed to initialize SDL_ttf: ",TTF_GetError());
        return;
    }

    srand(time(0)); // Initialize Random Seed
}

// Destructor
Application::~Application()
{
    // Free The Resources
    delete m_renderer;  // Clean up the Renderer

    font.ForceFree();

    highScoreFile.close();

    TTF_Quit();
}

void Application::Run()
{
    OnStart();

    while (Running()) {
        frameStart = SDL_GetTicks(); // Get the current time at the start of the frame

        HandleEvents();

        // Calculate deltaTime (in seconds)
        double deltaTime = (SDL_GetTicks() - frameStart) / 1000.0;

        OnUpdate(deltaTime);  // Pass delta time
        Draw();               // Draw the frame

        // Calculate how long the frame took
        Uint32 frameTime = SDL_GetTicks() - frameStart;

        // If the frame took less time than frameDelay, wait for the remaining time
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

// Check SDL Window Events Like Quit or Resize
void Application::HandleEvents()
{
    // Handle SDL Events
    while (SDL_PollEvent(&m_window_event))
    {
        // Application Quit Event
        if (m_window_event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        // Window Resize Event
        if (m_window_event.type == SDL_WINDOWEVENT)
        {
            if (m_window_event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                int newWidth = m_window_event.window.data1;
                int newHeight = m_window_event.window.data2;
                std::cout << "Window resized to " << newWidth << "x" << newHeight << std::endl;
            }
        }
    }
}

// Checks Whether App Is Currently Running Or Not
bool Application::Running()
{
    return isRunning;
}




// Called Once At The Start Of Program
void Application::OnStart()
{
   // Initialize The Audio System
    initAllAudio();

    SpaceBackgroundsList.InsertAtEnd(spaceBackgroundA);
    SpaceBackgroundsList.InsertAtEnd(spaceBackgroundB);

    // Read The High Score
    if (!highScoreFile)
    {
        Error::Print("<FileNotFoundError> ", "Input High Score Text File Couldn't Be Found");
    }

    

    std::string temp;
    highScoreFile >> temp;

    if (temp != "")
    {
        std::cout << "High Score: " << temp << std::endl;
        highScore = std::stoi(temp);
    }

    else
    {
        highScore = 0;
        highScoreFile << "0";

        Error::PrintExit("<EmptyHighScore> ", " : The High Score File Is Either Empty Or The High Score Isn't Present");
    }


    LoadScene(SCENE_MAIN_MENU);

    std::cout << "Current Scene : " << currentScene << std::endl;
    // Initialization code goes here
    Print::PinkLine("Application Started...");

    collisionManager.Init(OnCollisionWithObstacle,OnCollisionWithStar, OnCollisionWithStar2, OnCollisionWithStar3);


    // Load Textures
    playerTexture = m_renderer->LoadTexture(PLAYER_SPRITE_IMG_PATH, m_renderer->GetRenderer());
    spaceTexture = m_renderer->LoadTexture(SPACE_BACKGROUND_IMG_PATH, m_renderer->GetRenderer());  // Texture For Space Background
    starTexture = m_renderer->LoadTexture(COLLECTABLE_STAR_IMG_PATH, m_renderer->GetRenderer());
    rockTexture = m_renderer->LoadTexture(KILLER_ROCK_IMG_PATH, m_renderer->GetRenderer());
    mainMenuBGTexture = m_renderer->LoadTexture(MAIN_MENU_BACKGROUND, m_renderer->GetRenderer());
    gameOverBGTexture = m_renderer->LoadTexture(GAME_OVER_BACKGROUND, m_renderer->GetRenderer());
    buttonBGTexture = m_renderer->LoadTexture(BUTTON_BACKGROUND, m_renderer->GetRenderer());

    // Declare Sprites
    player = {600,600, 100, 150, playerTexture }; // Create a sprite
    spaceBackgroundA = { 0,-1080,1920,1080,spaceTexture };
    spaceBackgroundB = { 0,0,1920,1080,spaceTexture };
    star =  { 600,200, 100, 100, starTexture };
    star2 = { 300,400, 100, 100, starTexture };
    star3 = { 1000,700, 100, 100, starTexture };
    mainMenuBG = { 0,0, 1550, 750, mainMenuBGTexture };
    gameOverBG = { 0,0, 1550, 750, gameOverBGTexture };
    scoreButtonBG = {0, 0,250, 80, buttonBGTexture };
    starsButtonBG = { 1200, 1, 250, 80, buttonBGTexture };

     obstacleA  = { 100,100, 100, 100,rockTexture };
     obstacleB  = { 1200,250, 100, 100, rockTexture };
     obstacleC =  { 800, 550, 100, 100, rockTexture };
     obstacleD = { 1000,50, 100, 100, rockTexture };
     obstacleE = { 1300,800, 100, 100, rockTexture };

     // Load Objects In Layers
     ObstacleLayer_Gameplay.push_back(obstacleA);
     ObstacleLayer_Gameplay.push_back(obstacleB);
     ObstacleLayer_Gameplay.push_back(obstacleC);
     ObstacleLayer_Gameplay.push_back(obstacleD);
     ObstacleLayer_Gameplay.push_back(obstacleE);

    // Load The Font
    font.Load(ARIAL_FONT, 24);
    mainMenuFont.Load(ARIAL_FONT, 72);

    // Set Text Values
    scoreText.Set(30, 10, 191, 54, "Score: ", Color::Red);
    starsText.Set(1230, 10, 191, 54, "Stars: ", Color::Yellow);
    highScoreText.Set(30, 80, 191, 54, "Best: ", Color::Red);

   
    gameOverScoreText.Set(1, 1, 600, 120, "Score: ", Color::Green);


    // Set The Tags 
    player.SetTag("Player");
    star.SetTag("Star");
    star2.SetTag("Star2");
    star3.SetTag("Star3");

    player.ScaleX(-10);
    player.ScaleY(-10);
    
    // Set Tags For Obstacle
    for (auto& obstacle : ObstacleLayer_Gameplay)
    {
        obstacle.SetTag("Obstacle");
    }

    // Add All The Colliders Of Objects That Can Collide With Player
    collisionManager.AddCollider(&player.BoxCollider);
    collisionManager.AddCollider(&star.BoxCollider);
    collisionManager.AddCollider(&star2.BoxCollider);
    collisionManager.AddCollider(&star3.BoxCollider);

    // Add Colliders Of Obstacles To The CollisionManager
    for(auto& obstacle : ObstacleLayer_Gameplay)
    {
        collisionManager.AddCollider(&obstacle.BoxCollider); // Add other sprites as necessary
    
    }
    

    //player.showCollider = true;
    //star.showCollider = true;
    

   
}


// Called Each Frame
void Application::OnUpdate(double deltaTime)
{
    int playerSpeed = 15;
    static int tempScore = 0;
    static int speed = 3;
    static int scr = 150;
    static int speedIncreaseAfter = 50;

    // Update() For Gameplay Scene
    if (currentScene == SCENE_GAMEPLAY)
    {

      

        // Unlock Transforms
        player.lockTransform = false;
        star.lockTransform = false;
        star2.lockTransform = false;
        star3.lockTransform = false;

        for (auto& obstacle : ObstacleLayer_Gameplay)
        {
            obstacle.lockTransform = false;
        }

        // Player Movement
        if (Input::GetKey(RIGHT) or Input::GetKey(D))
        {
            if (player.BoxCollider.x < screenWidth * 2.88)
            {
                player.MoveRight(playerSpeed);
            }
        }
        


        if (Input::GetKey(LEFT) or Input::GetKey(A))
        {
            if (player.BoxCollider.x > 0)
            {
                player.MoveLeft(playerSpeed);
            }
        }

        // For Going To Main Menu
        if (Input::GetKey(ESC) )
        {
            LoadScene(SCENE_MAIN_MENU);
        }


        if (tempScore >= speedIncreaseAfter)
        {
            speedIncreaseAfter += 30;
            tempScore = 0;
            scr++;
        }

        // Move All The Obstacles Down
        for (auto& obstacle : ObstacleLayer_Gameplay)
        {
            obstacle.MoveDown(speed + scr);

            if (obstacle.y >= screenWidth * 2)
            {
                obstacle.x = Random::Range(0, screenWidth * 3);
                obstacle.y = -100;
            }
        }

        // Move Space Background
        spaceBackgroundA.MoveDown(speed + scr);
        spaceBackgroundB.MoveDown(speed + scr);

        if (spaceBackgroundB.y >= screenWidth * 2)
        {
            spaceBackgroundA.y = -1080;
            spaceBackgroundB.y = 0;
        }



        star.MoveDown(speed + scr);
        star2.MoveDown(speed + scr);
        star3.MoveDown(speed + scr);

        if (star.y >= screenWidth * 2)
        {
            star.y = -100;
            star.x = Random::Range(0, screenWidth * 2);
        }

        if (star2.y >= screenWidth * 2)
        {
            star2.y = -100;
            star2.x = Random::Range(0, screenWidth * 2);
        }

        if (star3.y >= screenWidth * 2)
        {
            star3.y = -100;
            star3.x = Random::Range(0, screenWidth * 2);
        }


        scoreText.content = "Score: " + std::to_string(score);
        starsText.content = "Stars: " + std::to_string(starsCount);
        highScoreText.content = "Best: " + std::to_string(highScore);

        collisionManager.CheckCollisions();

        score += 1;
        tempScore += 1;

    }

    // Update() For Main Menu Scene
    else if (currentScene == SCENE_MAIN_MENU)
    {
      
        

        // Reset The Variables
        playerSpeed = 12;
        score = 0;
        tempScore = 0;
        speed = 1;
        scr = 0;
        starsCount = 0;

        // Lock Transforms Of Everything
        player.lockTransform = true;
        star.lockTransform = true;
        star2.lockTransform = true;
        star3.lockTransform = true;

        int i = 0;
        for (auto& obstacle : ObstacleLayer_Gameplay)
        {
            switch (i)
            {
            case 0:
                obstacle.Move(Random::Range(0, screenWidth * 3),100);
                break;
            case 1:
                obstacle.Move(Random::Range(0, screenWidth*3),250);
                break;
            case 2:
                obstacle.Move(Random::Range(0, screenWidth * 3),550);
                break;
            case 3:
                obstacle.Move(Random::Range(0, screenWidth * 3),50);
                break;
            case 4:
                obstacle.Move(Random::Range(0, screenWidth * 3),800);
                break;
            }
            obstacle.lockTransform = true;
        }
        
        // Reset The Position Of Player
        player.x = 600;
        player.BoxCollider.x = 600;

        // Load Game
        if (Input::GetKeyDown(ENTER) or Input::GetKeyDown(SPACE))
        {
           LoadScene(SCENE_GAMEPLAY);
        }
        // Exit App
        if (Input::GetKeyDown(Q))
        {
            exit(0);
        }

    }

    // Update() For Game Over Scene
    else if(currentScene == SCENE_GAME_OVER)
    {


        // Reset The Variables
        playerSpeed = 12;
        
        tempScore = 0;
        speed = 1;
        scr = 0;
        starsCount = 0;

        gameOverScoreText.content = "Score : " + std::to_string(score);

        

        // Lock Transforms Of Everything
        player.lockTransform = true;
        star.lockTransform = true;
        star2.lockTransform = true;
        star3.lockTransform = true;

        int i = 0;
        for (auto& obstacle : ObstacleLayer_Gameplay)
        {
            switch (i)
            {
            case 0:
                obstacle.Move(Random::Range(0, screenWidth * 3), 100);
                break;
            case 1:
                obstacle.Move(Random::Range(0, screenWidth * 3), 250);
                break;
            case 2:
                obstacle.Move(Random::Range(0, screenWidth * 3), 550);
                break;
            case 3:
                obstacle.Move(Random::Range(0, screenWidth * 3), 50);
                break;
            case 4:
                obstacle.Move(Random::Range(0, screenWidth * 3), 800);
                break;
            }
            obstacle.lockTransform = true;
        }

        // Reset The Position Of Player
        player.x = 600;
        player.BoxCollider.x = 600;

        // Load Main Menu
        if (Input::GetKeyDown(M) or Input::GetKeyDown(ESC))
        {
            score = 0;
            LoadScene(SCENE_MAIN_MENU);
        }

        // Restart
        if (Input::GetKeyDown(R) or Input::GetKeyDown(ENTER))
        {
            score = 0;
            LoadScene(SCENE_GAMEPLAY);
        }
    }


}

// Called Each Frame
void Application::Draw()
{
    // Draw() For Gameplay Scene
    if (currentScene == SCENE_GAMEPLAY)
    {
        // Drawing code goes here
        m_renderer->Clear(); // Clear The Previous Contents In The Renderer

       
        // Draw Space background
        Node<Sprite>* head = SpaceBackgroundsList.GetHead();

        while (head->next != nullptr)
        {
            m_renderer->DrawSprite(head->data);
            head = head->next;
        }

        m_renderer->DrawSprite(spaceBackgroundA);
        m_renderer->DrawSprite(spaceBackgroundB);

        

        

        // Draw All The Obstacles In The Obstacle Layer
        for (auto& obstacle : ObstacleLayer_Gameplay)
        {
            m_renderer->DrawSprite(obstacle);
        }

        m_renderer->DrawSprite(star);
        m_renderer->DrawSprite(star2);
        m_renderer->DrawSprite(star3);

        



        // Draw The Player
        player.BoxCollider.color = Color::Green;
        m_renderer->DrawSprite(player);

        // Draw The UI
       m_renderer->DrawSprite(scoreButtonBG);
       m_renderer->DrawSprite(starsButtonBG);
       m_renderer->DrawText2D(scoreText, font, Color::New(247,231,216));
       m_renderer->DrawText2D(starsText, font, Color::White);
       m_renderer->DrawText2D(highScoreText, font, Color::Yellow);
        

        m_renderer->Present();
    }

    // Draw() For Main Menu Scene
    else if (currentScene == SCENE_MAIN_MENU)
    {
        m_renderer->Clear();

        m_renderer->DrawSprite(mainMenuBG);

        m_renderer->Present();
    }

    // Draw() For Game Over Scene
    else if (currentScene == SCENE_GAME_OVER)
    {
        m_renderer->Clear();

        m_renderer->DrawSprite(gameOverBG);

        m_renderer->DrawText2D(gameOverScoreText, mainMenuFont, Color::White);

        m_renderer->Present();
        
    }

}













