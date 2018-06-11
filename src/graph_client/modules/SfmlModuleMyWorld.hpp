//
// EPITECH PROJECT, 2018
// SfmlTests
// File description:
// SfmlModuleMyWorld.hpp
//

#ifndef SFMLTESTS_SFMLMODULEMYWORLD_HPP
#define SFMLTESTS_SFMLMODULEMYWORLD_HPP

#include "ISfmlModule.hpp"
#include "CsvParser.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <fstream>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <map>

# define M_PI 3.14159265358979323846  /* pi */
# define MIN(x, y) ((x) < (y) ? (x) : (y))
# define MAX(x, y) ((x) > (y) ? (x) : (y))

class MwProjector
{
public:
        enum Type {
                ISO,
                PARA,
                FLAT
        };

        MwProjector();

        void resetAngles(float rx, float ry, float rz);
        void setType(Type _type);
        sf::Vector2f projectPoint(sf::Vector3f);
        void setCenter(unsigned int center, unsigned int i);
private:
        std::array<double, 6> _r;
        Type _type = ISO;
        sf::Vector2f projectIso(sf::Vector3f vec3f);
        sf::Vector2f projectPara(sf::Vector3f vec3f);
        sf::Vector2f _center;
        int _heightRatio = 1;
};

typedef struct MwPoint_s {
        sf::Vector3f pt3d;
        sf::Vector2f pt2d;
} MwPoint;

class MwTile : public sf::Drawable, public sf::Transformable
{
public:
        void setColor(sf::Color color);
        void setTexture(const sf::Texture &m_texture);
        bool contain(sf::Vector2f point);
        bool isIntersect(sf::Vector2f vertex1, sf::Vector2f vertex2, sf::Vector2f point);
        bool setTile(std::vector<MwPoint> points);
private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
                states.transform *= getTransform();
                states.texture = &m_texture;
                target.draw(m_vertices, states);
        }
        sf::VertexArray m_vertices;
        sf::Texture m_texture;
        std::vector<sf::Vector3f> _3dCoords;
        MwProjector _projector;
};

class MwTileMap
{
public:
        void load(std::string filename);
        bool load(std::vector<std::vector<float>> tiles,
		int width, int height);
        explicit MwTileMap(sf::RenderWindow &_window) :
		_window(_window), _tileSize(32, 32), _projector() {}
        void draw();
        void setTileSize(const sf::Vector2i &_tileSize);
        void event();
        void updateTiles();
        void updatePointHeight(MwPoint &pt, int z = 10);
private:
        void initTiles();
        void initPoints(std::vector<std::vector<float>> z);
        std::vector<MwTile> _tiles;
        sf::RenderWindow &_window;
        sf::Vector2i _tileSize;
        MwProjector _projector;
        std::vector<MwPoint> _points;
        sf::Vector2<int> _size;
};

namespace zappy::client::module {
	class SfmlModuleMyWorld : public ISfmlModule {
	public:
		explicit SfmlModuleMyWorld(sf::RenderWindow &_window);
		ModuleStatus start() override;
		ModuleStatus update() override;
		void handleEvent(sf::Event &event) override;
		ModuleStatus close() override;
		std::string nextModule() override;

	private:
		sf::RenderWindow &_window;
		MwTileMap _map;
	};
}
#endif //SFMLTESTS_SFMLMODULEMYWORLD_HPP
