#include "Screen.h"

Screen::Screen(Spritesheet* sheet): 
	m_isClosed(false),
	m_xOffset(0), 
	m_yOffset(0)
{
	sf::Uint32 style = sf::Style::Default;

	sf::ContextSettings context;
	context.depthBits = 24;
	context.stencilBits = 8;
	context.antialiasingLevel = 2;

	m_sheet = sheet;

	m_w = FRAME_WIDTH / (FINAL_TILESIZE);
	m_h = FRAME_HEIGHT / (FINAL_TILESIZE);

	m_window.create(sf::VideoMode(FRAME_WIDTH, FRAME_HEIGHT, 32), "All aboard !! Thousand portholes", style, context);
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60);
}

Screen::~Screen()
{
	m_window.close();
}

sf::RenderWindow* Screen::getRenderWindow()
{
	return &m_window;
}

void Screen::clear()
{
	m_window.clear(sf::Color::Black);
}

void Screen::display()
{
	m_window.display();
}

void Screen::setOffset(int xOffset, int yOffset)
{
	m_xOffset = xOffset;
	m_yOffset = yOffset;
}

void Screen::close() {
	m_isClosed = true;
}

void Screen::render(int xp, int yp, int tile, int color, int flip)
{
	xp -= m_xOffset;
	yp -= m_yOffset;
	int x = tile % (TILE_SIZE * SCALE);
	int y = tile / (TILE_SIZE * SCALE);

	sf::Sprite s = m_sheet->getSprite(x, y, color, flip);
	s.setScale(sf::Vector2f(SCALE, SCALE));
	if (color != -1) {
		s.setColor(sf::Color(color));
	}
	s.setPosition(xp, yp);
	m_window.draw(s);
}

void Screen::render(int xp, int yp, int tile, int w, int h,int color, int flip)
{
	xp -= m_xOffset;
	yp -= m_yOffset;
	int x = tile % (TILE_SIZE * SCALE);
	int y = tile / (TILE_SIZE * SCALE);

	sf::Sprite s = m_sheet->getSprite(x, y, w, h, color, flip);
	s.setScale(sf::Vector2f(SCALE, SCALE));
	s.setPosition(xp, yp);
	m_window.draw(s);
}

void Screen::renderFont(int xp, int yp, int tile, int color) {
	xp -= m_xOffset;
	yp -= m_yOffset;
	int x = tile % (TILE_SIZE * SCALE * SCALE);
	int y = tile / (TILE_SIZE * SCALE * SCALE);

	sf::Sprite s = m_sheet->getFontSprite(x, y, 8, 16, color, 0);
	s.setScale(sf::Vector2f(SCALE, SCALE));
	s.setPosition(xp, yp);
	m_window.draw(s);
}

void Screen::renderSquare(int xp, int yp, int w, int h, int color) {
	sf::RectangleShape r;
	r.setSize(sf::Vector2f(w, h));
	r.setScale(sf::Vector2f(SCALE, SCALE));
	r.setPosition(xp, yp);
	r.setFillColor(sf::Color(color));
	m_window.draw(r);
}

int Screen::getWidth()
{
	return m_w;
}

int Screen::getHeight()
{
	return m_h;
}

bool Screen::isClosed()
{
	return m_isClosed;
}
