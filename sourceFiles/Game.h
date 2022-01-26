#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<sstream>
#include<iostream>
#include<vector>
#include<ctime>
#include<fstream>
//Struktura rury - dolna i górna
struct pipeSet{
    sf::RectangleShape up;
    sf::RectangleShape down;
};
//Stany przycisków: IDLE - neutralny, HOVER - najechany
enum button_states{BTN_IDLE = 0, BTN_HOVER};
/*
    Klasa która jest silnikiem gry
*/
class Game
{
private:
    //Zmienne gry

    //Obiekt window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    //Obiekt event
    sf::Event ev;

    //Zmienne związane z logiką gry
    bool gameStart;     //czy gra się uruchomiała
    bool firstGame;     //czy jesteśmy na początku gry
    bool leaderboardView;   //widok najlepszych wyników

    unsigned floatingTime;  //jak długo ptak ma się unosić w animacji na początku gry

    bool birdFeltDown;      //gdy ptak spadnie to można zrestartować grę klikając spacje zamiast restart
    bool spaceHeld;       
    bool jump;
    unsigned holeSize;      //jak duża ma być dziura między rurami
    unsigned pipeSpawnTime; //ile czasu ubyło od ostatniego spawnu rury
    unsigned pipeSpawnTimeMax;  //co ile rury mają się odradzać
    float pipeSpeed;        //prędkość poruszania się rur

    //Wygląd przycisku
    button_states leaderboardButtonState;
    button_states restartButtonState;
    button_states returnButtonState;

    //Czas po upływie którego dodawane są punkty
    float timeToScorePoint;
    int timePassed;

    //Czas skoku i maksymalny czas wznoszenia po którym następuje opadanie
    int jumpTimeMax;
    int jumpTime;
    unsigned points;

    //Tablica wyników
    std::vector<int> scores;

    //Czcionka
    sf::Font scoreFont;
    //Tekst wyświetlający ilość punktów
    sf::Text scoreText;
    //Tekst do tabeli wyników
    sf::Text leaderboardScore;
    //Tablica wyników
    std::vector<sf::Text> leaderboardScores;
    //Tekst Tabela wyników
    sf::Text leaderboardText;
    //Tekst restart
    sf::Text restartText;
    //Tekst powrót
    sf::Text returnText;
    //Tekst kliknij spacje aby zacząć
    sf::Text howtostartText;
    //Przycisk tabela
    sf::RectangleShape leaderboardButton;
    //Przycisk restart
    sf::RectangleShape restartButton;
    //Przycisk powrót
    sf::RectangleShape returnButton;

    //Obiekty gry
    sf::RectangleShape pipe[2]; //rura - dolna i górna
    std::vector<pipeSet> pipes; //tablica rur
    sf::RectangleShape bird;    //ptak
    sf::Texture birdTexture;    //tekstura ptaka
    sf::RectangleShape background; //tło
    sf::Texture backgroundTexture;    //tekstura tła
    sf::Vector2f mousePosView;  //pozycja myszki


    //Funkcje prywatne, są wywowyłane raz na początku gry
    void initializerVariables();    
    void initWindow();
    void initPipes();
    void initFonts();
    void initText();
    void initBird();
    void initBackground();
    void initButton();

public:
    //Konstruktor i destruktor klasy
    Game();
    ~Game();

    //Czy okno jest otwarte
    const bool running() const;

    //Funkcje
    void spawnPipes();  //spawnowanie rur
    void pollEvents();  //zamknij okno jeśli wcisniesz Esc
    void readLeaderboard(); //Czyta tablice z najlepszymi wynikami
    
    void updateView();      //Ustala które okno powinno być wyświetlane
    void updateMousePos();  //aktualizuje pozycje myszki gdy gra nie jest włączona
    void updateButton();    //zmienia kolorki przycisku
    void updateLeaderboard(); //Aktualizuje najlepsze wyniki
    void updateText();  //zmienia punkty
    void updatePipes(); //zmienia położenie rur
    void update();      //zarządza wszystkimi funkcjami update
    void updateBird();  //porusza ptakiem
    void collisionDetector();   //sprawdza czy ptak wleciał w rure lub czy nie spadł na ziemię

    void floatingBird();    //animacja ptaka na początku gry

    void renderBackground(); //renderowanie tła
    void renderLeaderboard();   //renderowanie okna najlepszych wyników
    void renderButton();    //rednerowanie przycisku
    void renderBird();  //renderowanie ptaka
    void renderText();  //renderowanie wyniku
    void renderPipes(); //renderowanie rur
    void render();      //zarządza wszystkimi funkcjami render

};