//
// EPITECH PROJECT, 2018
// SfmlTests
// File description:
// SfmlModuleMyWorld.cpp
//

#include "SfmlModuleMyWorld.hpp"

class token_grid;

bool MwTile::isIntersect(sf::Vector2f vertex1, sf::Vector2f vertex2, sf::Vector2f point)
{
        if (((vertex1.y <= point.y) && (vertex2.y > point.y)) ||
                ((vertex1.y > point.y) && (vertex2.y <=  point.y))) {
                float vt = (float) (point.y - vertex1.y) / (vertex2.y - vertex1.y);
                return (point.x < vertex1.x + vt * (vertex2.x - vertex1.x));
        }
        return false;
}

bool MwTile::contain(sf::Vector2f point)
{
        return static_cast<bool>(
                (isIntersect(m_vertices[0].position,
                             m_vertices[1].position, point) +
                 isIntersect(m_vertices[0].position,
                             m_vertices[2].position, point) +
                 isIntersect(m_vertices[3].position,
                             m_vertices[1].position, point) +
                 isIntersect(m_vertices[3].position,
                             m_vertices[2].position, point)) & 1);
}



bool MwTile::setTile(std::vector<MwPoint> points)
{
        if (points.size() < 4)
                return false;
        m_vertices.setPrimitiveType(sf::TriangleStrip);
        m_vertices.resize(4);
        m_vertices.getBounds();
        for (int i = 0; i < 4; i++)
                m_vertices[i].position = points[i].pt2d;
        return true;
}

void MwTile::setTexture(const sf::Texture &m_texture)
{
        MwTile::m_texture = m_texture;
        m_vertices[0].texCoords = sf::Vector2f(0, 0);
        m_vertices[1].texCoords = sf::Vector2f(m_texture.getSize().x, 0);
        m_vertices[2].texCoords = sf::Vector2f(0, m_texture.getSize().y);
        m_vertices[3].texCoords = sf::Vector2f(m_texture.getSize().x,
                                                m_texture.getSize().y);
}

void MwTile::setColor(sf::Color color) {
        for (size_t i = 0; i < m_vertices.getVertexCount(); ++i)
                m_vertices[i].color = color;
}

void MwTileMap::initPoints(std::vector<std::vector<float>> z) {
        _points.clear();
        _points.resize((unsigned long)_size.x * _size.y);
        for (int i = 0; i < _size.x; ++i)
                for (int j = 0; j < _size.y; ++j) {
                        sf::Vector3f pt3d
                                ((i - (float)(_size.x - 1)/2) * _tileSize.x,
                                (j - (float)(_size.y - 1)/2) * _tileSize.y,
                                 z[j][i]);
                        sf::Vector2f pt2d = _projector.projectPoint(pt3d);
                        _points[j * _size.x + i] = {pt3d, pt2d};
                }
}

void MwTileMap::initTiles() {
        std::vector<sf::Texture> textures(1);
        textures[0].loadFromFile("../assets/grassTexture.png");
        _tiles.resize((unsigned int)(_size.x - 1) * (_size.y - 1));
        for (int i = 0; i < _size.x - 1; ++i)
                for (int j = 0; j < _size.y - 1; ++j)
                {
                        MwTile tile;
                        std::vector<MwPoint> positions(4);
                        positions[0] = _points[j * _size.x + i];
                        positions[1] = _points[j * _size.x + i + 1];
                        positions[2] = _points[(j + 1) * _size.x + i];
                        positions[3] = _points[(j + 1) * _size.x + i + 1];
                        if (abs((int)(positions[0].pt3d.z
                                        - positions[3].pt3d.z)) <
                            abs((int)(positions[1].pt3d.z
                                        - positions[2].pt3d.z))) {
                                std::iter_swap(positions.begin(),
                                                positions.begin() + 1);
                                std::iter_swap(positions.begin() + 3,
                                                positions.begin() + 2);
                        }
                        tile.setTile(positions);
                        tile.setTexture(textures[rand() % textures.size()]);
                        _tiles[i + j * (_size.x - 1)] = tile;
                }
}

bool MwTileMap::load(std::vector<std::vector<float>> tiles,
                        int width, int height)
{
        _size = sf::Vector2i(width, height);
        _tiles.resize(((unsigned int)(width - 1) * (height - 1)));
        _projector.setType(MwProjector::ISO);
        _projector.setCenter(_window.getSize().x / 2, _window.getSize().y / 2);
        int tilesize = (int) (MIN(_window.getSize().x, _window.getSize().y)
                                / MAX(tiles.size(), tiles[0].size()) / 2);
        this->_tileSize = sf::Vector2i(tilesize, tilesize);
        initPoints(tiles);
        initTiles();
        return true;
}

void MwTileMap::load(std::string filename)
{
        std::ifstream file(filename);
        std::vector<std::vector<float>> map;
        size_t y = 0;

        for(CSVIterator loop(file); loop != CSVIterator(); ++loop)
        {
                map.resize(y + 1);
                map[y].resize((*loop).size());
                for (size_t x = 0; x < (*loop).size(); x++) {
                        map[y][x] = static_cast<float>
                        (atof((*loop)[x].c_str()));
                }
                y++;
        }
        load(map, static_cast<int>(map[0].size()),
             static_cast<int>(map.size()));
}

void MwTileMap::draw() {
        for (auto &tile : _tiles)
                _window.draw(tile);
}

void MwTileMap::setTileSize(const sf::Vector2i &_tileSize)
{
        MwTileMap::_tileSize = _tileSize;
}

void MwTileMap::updatePointHeight(MwPoint &pt, int z)
{
        pt.pt3d.z += z;
        sf::Vector2f pt2d = _projector.projectPoint(pt.pt3d);
        pt.pt2d.x = pt2d.x;
        pt.pt2d.y = pt2d.y;
}

void MwTileMap::event()
{
}

void MwProjector::setType(MwProjector::Type _type)
{
        MwProjector::_type = _type;
}

MwProjector::MwProjector() :
        _r{0, 0, 0, 0, 0, 0}, _center{0, 0}, _heightRatio(1)
{
        resetAngles(0, 0, 0);
}

sf::Vector2f MwProjector::projectIso(sf::Vector3f pos3d)
{
        sf::Vector2f pos2d;
        float x;
        float y;
        float z;

        x = (float)(pos3d.x * _r[2] * _r[1]
                + pos3d.y * (_r[2] * _r[4] * _r[3] - _r[0] * _r[5])
                + pos3d.z * (_r[5] * _r[3] + _r[2] * _r[0] * _r[4]));
        y = (float)(pos3d.x * _r[1] * _r[5]
                + pos3d.y * (_r[2] * _r[0] + _r[5] * _r[4] * _r[3])
                + pos3d.z * (_r[0] * _r[5] * _r[4] - _r[2] * _r[3]));
        z = pos3d.x * -_r[4] + pos3d.y * (_r[1] * _r[3])
                + pos3d.z * (_r[1] * _r[0]);
        pos2d.x = (float)(x * cos(M_PI / 6) + y * cos(5 * M_PI / 6))
                        + _center.x;
        pos2d.y = (float)(x * sin(M_PI / 6) + (y - z) * sin(5 * M_PI / 6))
                        + _center.y;
        return pos2d;
}

sf::Vector2f MwProjector::projectPara(sf::Vector3f vec3f)
{
        return {vec3f.x, vec3f.y};
}

sf::Vector2f MwProjector::projectPoint(sf::Vector3f vec3f)
{
        switch(_type) {
                case Type::ISO :
                        return projectIso(vec3f);
                case Type::PARA :
                        return projectPara(vec3f);
                default :
                        return {vec3f.x, vec3f.y};
        }
}

void MwProjector::resetAngles(float rx, float ry, float rz)
{
        _r[0] = std::cos(rx);
        _r[1] = std::cos(ry);
        _r[2] = std::cos(rz);
        _r[3] = std::sin(rx);
        _r[4] = std::sin(ry);
        _r[5] = std::sin(rz);
}

void MwProjector::setCenter(unsigned int x, unsigned int y)
{
        _center.x = x;
        _center.y = y;
}

zappy::client::module::SfmlModuleMyWorld::SfmlModuleMyWorld
        (sf::RenderWindow &_window) : _window(_window), _map(_window)
{
        _map.setTileSize(sf::Vector2i(50, 50));
        _map.load("../map.zpy");
}

zappy::client::module::ModuleStatus
zappy::client::module::SfmlModuleMyWorld::update()
{
        _map.draw();
        _map.event();
	return CONTINUE;
}

zappy::client::module::ModuleStatus
zappy::client::module::SfmlModuleMyWorld::start()
{
        return BEGIN;
}

void zappy::client::module::SfmlModuleMyWorld::handleEvent(sf::Event &event)
{
	(void) event;
}

zappy::client::module::ModuleStatus
zappy::client::module::SfmlModuleMyWorld::close()
{
        return END;
}

std::string zappy::client::module::SfmlModuleMyWorld::nextModule()
{
        return "";
}
