#include"Game.h"

//Konstruktor
Game::Game()
{
    this->initializerVariables();
    this->initWindow();
    this->initPipes();
    this->initFonts();
    this->initButton();
    this->initText();
    this->initBird();
    this->initBackground();
    this->readLeaderboard();
    
}
//Destruktor
Game::~Game()
{
    delete this->window;
}
//Funckja initializująca podstawowe zmienne
void Game::initializerVariables()
{
    this->window = nullptr;

    //Logika gry
    this->points = 0;
    this->gameStart = false;
    this->jump = false;
    this->holeSize = 160;
    this->pipeSpawnTimeMax = 100;
    this->pipeSpeed = 3.5;

    this->firstGame = true;
    this->leaderboardView = false;

    this->floatingTime = 30;

    this->birdFeltDown = false;

    //Ustawienia okna: szerokość i wysokość
    this->videoMode.width = 800;
    this->videoMode.height = 600;

    //Czas
    this->jumpTime = 0;
    this->jumpTimeMax = 19;
    this->timeToScorePoint = (this->videoMode.width/2 + 30 + 60) / this->pipeSpeed;
    this->timePassed = 0;

}
//Initializowanie okna
void Game::initWindow()
{
    this->window = new sf::RenderWindow(this->videoMode, "My Game", sf::Style::Default);
    //Ilość klatek do 60fps
    this->window->setFramerateLimit(60);
}
//Initializowanie rur
void Game::initPipes()
{
    this->pipe[0].setFillColor(sf::Color::Green);
    this->pipe[1].setFillColor(sf::Color::Green);
}
//Initializowanie ptaka
void Game::initBird()
{
    this->bird.setSize(sf::Vector2f(60.f, 60.f));
    this->bird.setPosition(this->videoMode.width/2.f - this->bird.getSize().x/2.f, this->videoMode.height/2.f - this->bird.getSize().y);
    //Załadowanie tekstury ptaka
    if(!this->birdTexture.loadFromFile("image/bird.png")) std::cout << "Error with  loading bird texture\n";
    //Ustawienie tekstury ptaku
    this->bird.setTexture(&birdTexture);
}
//Inicjalizowanie tła
void Game::initBackground()
{   
    this->background.setSize(sf::Vector2f(this->videoMode.width, this->videoMode.height));
    this->background.setPosition(0.f, 0.f);
    //Załadowanie tekstury tła
    if(!this->backgroundTexture.loadFromFile("image/background.png")) std::cout << "Error with  loading background texture\n";
    //Ustawienie tekstury dla tła
    this->background.setTexture(&backgroundTexture);
}
//Ustawianie czcionki
void Game::initFonts()
{
    //Załadowanie czcionki
    if(!this->scoreFont.loadFromFile("Fonts/VT323-Regular.ttf"))
        std::cout<<"FONTS::Error::couldn't load fonts\n";
}
//Przypisywanie dla tekstu czcionki, wielkości i koloru
void Game::initText()
{
    this->scoreText.setFont(this->scoreFont);
    this->scoreText.setCharacterSize(72);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setPosition(this->videoMode.width / 2 - 10, 50.f);

    this->howtostartText.setFont(this->scoreFont);
    this->howtostartText.setCharacterSize(42);
    this->howtostartText.setFillColor(sf::Color::White);
    this->howtostartText.setPosition(this->videoMode.width / 2 - 250, 550.f);
    this->howtostartText.setString("Nacisnij SPACJE aby rozpoczac");

    this->leaderboardScore.setFont(this->scoreFont);
    this->leaderboardScore.setCharacterSize(32);
    this->leaderboardScore.setFillColor(sf::Color::White);

    this->leaderboardText.setFont(this->scoreFont);
    this->leaderboardText.setCharacterSize(32);
    this->leaderboardText.setFillColor(sf::Color::White);
    this->leaderboardText.setString("Wyniki");
    this->leaderboardText.setOrigin(
        this->leaderboardText.getLocalBounds().left + this->leaderboardText.getLocalBounds().width / 2.f,
        this->leaderboardText.getLocalBounds().top + this->leaderboardText.getLocalBounds().height / 2.f
    );
    this->leaderboardText.setPosition(
        this->leaderboardButton.getPosition().x + this->leaderboardButton.getGlobalBounds().width / 2.f,
        this->leaderboardButton.getPosition().y + this->leaderboardButton.getGlobalBounds().height / 2.f
    );

    this->restartText.setFont(this->scoreFont);
    this->restartText.setCharacterSize(32);
    this->restartText.setFillColor(sf::Color::White);
    this->restartText.setString("Restart");
    this->restartText.setOrigin(
        this->restartText.getLocalBounds().left + this->restartText.getLocalBounds().width / 2.f,
        this->restartText.getLocalBounds().top + this->restartText.getLocalBounds().height / 2.f
    );
    this->restartText.setPosition(
        this->restartButton.getPosition().x + this->restartButton.getGlobalBounds().width / 2.f,
        this->restartButton.getPosition().y + this->restartButton.getGlobalBounds().height / 2.f
    );

    this->returnText.setFont(this->scoreFont);
    this->returnText.setCharacterSize(32);
    this->returnText.setFillColor(sf::Color::White);
    this->returnText.setString("Powrot");
    this->returnText.setOrigin(
        this->returnText.getLocalBounds().left + this->returnText.getLocalBounds().width / 2.f,
        this->returnText.getLocalBounds().top + this->returnText.getLocalBounds().height / 2.f
    );
    this->returnText.setPosition(
        this->returnButton.getPosition().x + this->returnButton.getGlobalBounds().width / 2.f,
        this->returnButton.getPosition().y + this->returnButton.getGlobalBounds().height / 2.f
    );
}
//Tworzenie przycisków
void Game::initButton()
{
    this->leaderboardButtonState = BTN_IDLE;
    this->restartButtonState = BTN_IDLE;
    this->returnButtonState = BTN_IDLE;

    this->leaderboardButton.setPosition(this->videoMode.width / 2 - 75, 350.f);
    this->leaderboardButton.setSize(sf::Vector2f(150.f, 80.f));
    this->leaderboardButton.setFillColor(sf::Color(10,10,10,255));
    
    this->restartButton.setPosition(this->videoMode.width / 2 - 75, 450.f);
    this->restartButton.setSize(sf::Vector2f(150.f, 80.f));
    this->restartButton.setFillColor(sf::Color(10,10,10,255));

    this->returnButton.setPosition(this->videoMode.width / 2 - 75, 450.f);
    this->returnButton.setSize(sf::Vector2f(150.f, 80.f));
    this->returnButton.setFillColor(sf::Color(10,10,10,255));

}
//Czy okno jest wciąż otwarte
const bool Game::running() const
{
    return this->window->isOpen();
}
//Czytanie wyników z pliku tablica-wynikow.txt
void Game::readLeaderboard()
{
    std::fstream plik;
    plik.open("tablica-wynikow.txt", std::ios::in);
    if(plik.good()){
        int score;
        while(plik >> score){
            //dodanie wyniku to tablicy scores
            scores.push_back(score);
        }
    } else std::cout<<"Nie udalo sie otworzyc pliku tablica-wynikow.txt";
    plik.close();
    
}
//Aktualizowanie tablicy wyników
void Game::updateLeaderboard()
{
    //Zdażało się że czytało więcej niż 5 elementów z pliku więc obcinamy do 5
    while(scores.size() > 5) scores.pop_back();
    //Jeśli zdobyte punkty są większe od najmniejszego wyniku na liście, lub tablica ma mniej niż 5 elementów
    //Należy zdobyć więcej niż 0 punktów aby zaktualizować tablice
    if(this->points > scores.back() || scores.size() < 5 && this->points > 0){
        int i = scores.size()-1;
        //Na którym miejscu wynik powinien się znaleźć
        while(this->points > scores[i]){
            i--;
        }
        //Wkładamy wynik w odpowiednie miejsce w tablicy
        scores.insert(scores.begin() + i + 1, this->points);
        //Jeśli jest teraz 6 elementów to obcinamy do 5
        while(scores.size() > 5) scores.pop_back();
        //Ten kawałek do ofs.close() służy do wyczyszczenia pliku aby wpisać tam nowe dane, a nie bawić się w edytowanie całego pliku
        std::ofstream ofs;
        ofs.open("tablica-wynikow.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        //Wkładamy zaktualizowaną tablicę do pliku
        std::fstream plik;
        plik.open("tablica-wynikow.txt", std::ios::out);
        if(plik.is_open())
        {
            for(int i=0; i<scores.size(); i++){
                plik << scores[i] << std::endl;
            }
        }
    }
    //Za każdym razem trzeba wyczyścić bo by rosła za każdym wejściem do okna Wyniki
    this->leaderboardScores.clear();
    //Tworzymy tekst do każdego wyniku i zapisujemy do tablicy leaderboardScores które później wyświetlamy
    for(int i=0; i<scores.size(); i++)
    {
        //i*50 aby był odstęp między wierszami
        this->leaderboardScore.setPosition(this->videoMode.width / 2 - 75, 100.f + i*50);
        std::stringstream ss;
        ss << i+1 << ".       " << scores[i] << " pkt";
        this->leaderboardScore.setString(ss.str());
        this->leaderboardScores.push_back(this->leaderboardScore);
    }
}

//Spawn rur
void Game::spawnPipes()
{
    //randomowe ustawienie wielkości dolnej rury
    int randSize = rand() % (this->videoMode.height - this->holeSize - 100) + 50;
    this->pipe[0].setPosition(static_cast<float>(this->videoMode.width), 0.f);
    this->pipe[0].setSize(sf::Vector2f(60.f, static_cast<float>(randSize)));

    //Ustawienie wielkości górnej rury uwzględniając wielkość dolnej i odstępu (holeSize)
    this->pipe[1].setPosition(static_cast<float>(this->videoMode.width), static_cast<float>(randSize+this->holeSize));
    this->pipe[1].setSize(sf::Vector2f(60.f, static_cast<float>(this->videoMode.height - randSize - this->holeSize)));
    //Dodanie obu rur do tablicy zawierającej obecnie wygenerowane rury
    this->pipes.push_back({this->pipe[0], this->pipe[1]});
}
//Funckja aktualizująca położnie rury
void Game::updatePipes()
{
    if(this->gameStart){
        //Jeśli minął czas pipeSpawnTimeMax -> wygeneruj nową rure
        if(this->pipeSpawnTime >= this->pipeSpawnTimeMax)
        {
            this->spawnPipes();
            this->pipeSpawnTime = 0;
        } else this->pipeSpawnTime++;
        //Przesuwanie rur w lewo
        for(int i=0; i<this->pipes.size(); i++)
        {
            this->pipes[i].up.move(-this->pipeSpeed, 0.f);
            this->pipes[i].down.move(-this->pipeSpeed, 0.f);
            //Jeśli rura wyszła poza okno -> usuń ją
            if(this->pipes[i].up.getPosition().x < -this->pipe[0].getSize().x)
            {
                this->pipes.erase(this->pipes.begin()+i);
                i--;
            }
        }
    }
}
//Aktualizacja ptaka
void Game::updateBird()
{
    //Jeśli gra jest rozpoczęta
    if(this->gameStart){
        //Spacja robi skok
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            if(this->spaceHeld == false){
                this->spaceHeld = true;
                this->jump = true;
                this->jumpTime = 0;
            }
        } else this->spaceHeld = false;
        //Jeśli był skok to podskocz ptakiem
        if(this->jump){
            this->bird.move(0.f, - (this->jumpTimeMax-this->jumpTime)*0.4);
            this->jumpTime++;
            //Czas skoku dobiegł końca
            if(this->jumpTime >= this->jumpTimeMax){
                this->jump = false;
                this->jumpTime = 0; 
            } 
        }
        else{
            //Grawitacja ściągająca w dół
            this->jumpTime++;
            this->bird.move(0.f, this->jumpTime*0.4);
            //Ograniczenie przyśpieszenia grawitacji
            if(this->jumpTime > 35) this->jumpTime = 35;
        }
    }else{
        //Jeśli trafiliśmy na rurę i ptak już spadł, można użyć spacji aby wznowić grę
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->birdFeltDown){
            this->bird.setPosition(this->videoMode.width/2.f - this->bird.getSize().x/2.f, this->videoMode.height/2.f - this->bird.getSize().y);
            this->gameStart = true;
            this->spaceHeld = true;
            this->jump = true;
            this->pipeSpawnTime = this->pipeSpawnTimeMax;
            //Czyszczenie
            this->pipes.clear();
            this->points = 0;
            this->timePassed = 0;
            this->birdFeltDown = false;
        } else{
            //Ptak spada na ziemię
            if(this->bird.getPosition().y < this->videoMode.height - this->bird.getSize().y){
                this->bird.move(0.f, 7.f);
            }
        }
    }
}
//Typowe dla SFML - można zamknąć program na ESC
void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev)){
        switch(ev.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(ev.key.code == sf::Keyboard::Escape) this->window->close();
                break;
        }
    }
}
//Aktualizuje pozycję myszki
void Game::updateMousePos()
{
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
void Game::updateButton()
{
    //Stan bezczynny przycisków
    this->leaderboardButtonState = BTN_IDLE;
    this->restartButtonState = BTN_IDLE;
    this->returnButtonState = BTN_IDLE;
    //Przycisk Tabela wyników najechany przez myszkę
    if(this->leaderboardButton.getGlobalBounds().contains(this->mousePosView))
    {
        //Jeśli najechany to zmień stan
        this->leaderboardButtonState = BTN_HOVER;
    }
    //Ustaw odpowiednio kolor
    switch(this->leaderboardButtonState)
    {
        case BTN_IDLE:
            this->leaderboardButton.setFillColor(sf::Color(50,50,50,255));
            break; 
        case BTN_HOVER:
            this->leaderboardButton.setFillColor(sf::Color(100,100,100,255));
            break;
    }
    //Przycisk Restart najechany przez myszke
    if(this->restartButton.getGlobalBounds().contains(this->mousePosView))
    {
        this->restartButtonState = BTN_HOVER;
    }
    switch(this->restartButtonState)
    {
        case BTN_IDLE:
            this->restartButton.setFillColor(sf::Color(50,50,50,255));
            break; 
        case BTN_HOVER:
            this->restartButton.setFillColor(sf::Color(100,100,100,255));
            break;
    }
    if(this->returnButton.getGlobalBounds().contains(this->mousePosView))
    {
        this->returnButtonState = BTN_HOVER;
    }
    switch(this->returnButtonState)
    {
        case BTN_IDLE:
            this->returnButton.setFillColor(sf::Color(50,50,50,255));
            break; 
        case BTN_HOVER:
            this->returnButton.setFillColor(sf::Color(100,100,100,255));
            break;
    }
}
//Zmienia punkty i text wyświetlający punkty
void Game::updateText()
{
    std::stringstream ss;
    if(!this->gameStart){
        //Pokaż wynik jeśli skończyłeś runde
        if(this->timePassed > 0) ss << this->points;
        else ss << "";
    }
    //Dodawanie punktów w trakcie gry
    else {
        if(this->points == 0){
            //Czas obliczony kiedy rura przekroczy dany punkt, wtedy zdobądź punkt
            if(this->timePassed > this->timeToScorePoint){
                this->timePassed = 0;
                this->points++;
            } else this->timePassed++;
        }
        else {
            //Wykorzystanie czasu spawnu rur aby dodać punkty
            if(this->timePassed > this->pipeSpawnTimeMax)
            {
                this->timePassed = 0;
                this->points++;
            } else this->timePassed++;
        }
        //zapisanie do strumienia
        ss << this->points;
    }
    this->scoreText.setString(ss.str());
}
void Game::collisionDetector()
{
    //Sprawdzanie czy ptak trafił na rurę
    for(int i=0; i<this->pipes.size(); i++){
        if(this->pipes[i].up.getGlobalBounds().intersects(this->bird.getGlobalBounds()) || this->pipes[i].down.getGlobalBounds().intersects(this->bird.getGlobalBounds()))
        {
            if(this->gameStart) updateLeaderboard();
            this->gameStart = false;
        }
    }
    //Sprawdzanie czy ptak spadł na ziemię
    if(this->bird.getPosition().y + this->bird.getSize().y >= this->videoMode.height){
        if(this->gameStart) updateLeaderboard();
        this->gameStart = false;
        this->birdFeltDown = true;
    }
}
//animacja ptaka na początku gry
void Game::floatingBird()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        //Jeśli była spacja to rozpocznij grę
        this->firstGame = false;
        this->gameStart = true;
        this->spaceHeld = true;
        this->jump = true;
        this->pipeSpawnTime = this->pipeSpawnTimeMax;
        this->jumpTime = 0;
    } else{
        //Jeśli nie było spacji to kontynuuj animacje
        if(this->jump){
            this->bird.move(0.f, (this->floatingTime - this->jumpTime)*-0.1);
            this->jumpTime++;
            if(this->floatingTime < this->jumpTime){
                this->jump = false;
                this->jumpTime = 0;
            } 
        } else{
            this->jumpTime++;
            this->bird.move(0.f, this->jumpTime*0.1);
            if(this->jumpTime > 29){
                this->jump = true;
                this->jumpTime = 0;
            }
        }
    }
}
//Zmień widok
void Game::updateView()
{
    //okno tabeli wyników
    if(this->leaderboardView)
    {
        if(this->returnButton.getGlobalBounds().contains(this->mousePosView))
        {
            //Mysz musi być najechana na przycisk i kliknięta
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //ustawienie zmiennych do pozycji startowych
                this->bird.setPosition(this->videoMode.width/2.f - this->bird.getSize().x/2.f, this->videoMode.height/2.f - this->bird.getSize().y);
                this->pipeSpawnTime = this->pipeSpawnTimeMax;
                this->pipes.clear();
                this->points = 0;
                this->timePassed = 0;
                this->leaderboardView = false;
                this->firstGame = true;
                this->birdFeltDown = false;
            }
        }
    }
    //okno początkowe
    else if(this->firstGame || !this->gameStart)
    {
        //przycisk Wyniki
        if(this->leaderboardButton.getGlobalBounds().contains(this->mousePosView))
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->points = 0;
                updateLeaderboard();
                this->leaderboardView = true;
                this->birdFeltDown = false;
            }
        }
        //Przycisk Restart
        if(this->restartButton.getGlobalBounds().contains(this->mousePosView) && !this->firstGame)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //ustawienie zmiennych do pozycji startowych
                this->bird.setPosition(this->videoMode.width/2.f - this->bird.getSize().x/2.f, this->videoMode.height/2.f - this->bird.getSize().y);
                this->gameStart = true;
                this->spaceHeld = true;
                this->jump = true;
                this->pipeSpawnTime = this->pipeSpawnTimeMax;
                this->pipes.clear();
                this->points = 0;
                this->timePassed = 0;
                this->birdFeltDown = false;
            }
        }
    }
}
//główna funkcja update
void Game::update()
{
    this->pollEvents();
    this->updateView();
    this->updateMousePos();
    if(!this->leaderboardView)
    {
        if(this->firstGame){
            this->floatingBird();
        } else
        {
            this->updateBird();
            this->updatePipes();
        }
    }
    this->updateText();
    this->updateButton();
    this->collisionDetector();
}
//renderowanie rur
void Game::renderPipes()
{
    //skrócony zapis normalnego fora, trzeba nauczyć się go stosować
    for(auto &e : this->pipes){
        this->window->draw(e.up);
        this->window->draw(e.down);
    }
}
//renderowanie ptaka
void Game::renderBird()
{
    this->window->draw(this->bird);
}
//renderowanie tła
void Game::renderBackground()
{
    this->window->draw(this->background);
}
//renderowanie tekstu dla przycisków oraz liczby punktów
void Game::renderText()
{
    //Odpowiednie renderowanie tekstu w zależności w którym oknie lub stanie gry się znajdujemy
    if(!this->leaderboardView)
    {
        this->window->draw(this->scoreText);
        if(!this->gameStart){
            this->window->draw(this->leaderboardText);
            if(!this->firstGame){
               this->window->draw(this->restartText);
            } else{
                this->window->draw(this->howtostartText);
            }
        }
    } else
    {
        this->window->draw(this->returnText);
    }
}
//rendoerwanie przycisku
void Game::renderButton()
{
    //Podobnie jak dla tekstu
    if(!this->gameStart && !this->leaderboardView)
    {
        this->window->draw(this->leaderboardButton);
        if(!this->firstGame)
            this->window->draw(this->restartButton);
    } else if(!this->gameStart && this->leaderboardView)
    {
        this->window->draw(this->returnButton);
    }
}
//renderowanie tabeli wyników
void Game::renderLeaderboard()
{
    for(int i=0; i<scores.size(); i++)
    {
        this->window->draw(this->leaderboardScores[i]);
    }
}
//główna fukncja render
void Game::render()
{
    /*
        -wyczyść starą ramkę
        -wyrenderuj obiekt
        -wyświetl ramkę w oknie
    */
    this->window->clear(sf::Color(0,0,0,255));

    this->renderBackground();
    if(!this->leaderboardView)
    {
        this->renderPipes();
        this->renderBird();
    } else 
    {
        this->renderLeaderboard();
    }
    this->renderButton();
    this->renderText();
    this->window->display();
}