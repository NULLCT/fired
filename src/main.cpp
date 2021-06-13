#include <SFML/Graphics.hpp>
#include <ctime>
#include <random>
using namespace std;

constexpr int FIRERECTCNT = 25;

void genFire(vector<vector<int>> &fire_color) { // 0 .. 256
  for (auto &&i : fire_color[FIRERECTCNT - 1])
    i = rand() % 256;

  for (int i = FIRERECTCNT - 2; i >= 0; i--) {
    for (int j = 0; j < FIRERECTCNT; j++) {
      /*
       *  * @ *
       *    *
       */
      int sum = 0;

      if (0 < j)
        sum += fire_color[i][j - 1];
      if (j + 1 < FIRERECTCNT)
        sum += fire_color[i][j + 1];
      sum += fire_color[i + 1][j];

      if (sum == 0)
        return;

      fire_color[i][j] = sum / 3;
    }
  }
}

int main() {
  srand(time(NULL));
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "fired");
  window.setFramerateLimit(60);

  vector<vector<int>> fire_color(FIRERECTCNT, vector<int>(FIRERECTCNT));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      }
    }
    window.clear();

    genFire(fire_color);

    for (int i = FIRERECTCNT - 1; i >= 0; i--) {
      bool tr = false;
      for (int j = 0; j < FIRERECTCNT; j++) {
        if (fire_color[i][j] != 0)
          tr = true;
        sf::RectangleShape rect(
            sf::Vector2f(float(window.getSize().x) / FIRERECTCNT,
                         float(window.getSize().y) / FIRERECTCNT));
        rect.setFillColor(sf::Color(fire_color[i][j], 0, 0));
        rect.setPosition(j * float(window.getSize().x) / FIRERECTCNT,
                         i * float(window.getSize().y) / FIRERECTCNT);
        window.draw(rect);
      }
      if (not tr)
        break;
    }

    window.display();
  }
}
