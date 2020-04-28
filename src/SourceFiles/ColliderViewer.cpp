#include "ColliderViewer.h"
#include "Resources.h"

ColliderViewer::ColliderViewer() :
    Viewer(Resources::Transparent) {
}

void ColliderViewer::init() {
	Viewer::init();
	renderer_ = SDL_Game::instance()->getRenderer();
	points_ = new SDL_Point[5];
    body_ = collider_->getBody();
    PIXELS_PER_METER = CONST(double, "PIXELS_PER_METER");
}

void ColliderViewer::drawRect(int index) const {
    setPoints(collider_->getRectRender(index).x, collider_->getRectRender(index).y, collider_->getW(index) * PIXELS_PER_METER, collider_->getH(index) * PIXELS_PER_METER);
    SDL_RenderDrawLines(renderer_, points_, 5);
}

void ColliderViewer::setPoints(double originX, double originY, double width, double height) const {

    b2Vec2 center = { (float)(originX + width), (float)(originY + height) };
    float angle = -collider_->getAngle();

	points_[0].x = center.x - width * cos(angle) - height * sin(angle);
    points_[0].y = center.y - width * sin(angle) + height * cos(angle);

    points_[1].x = center.x + width * cos(angle) - height * sin(angle);
    points_[1].y = center.y + width * sin(angle) + height * cos(angle);

    points_[2].x = center.x + width * cos(angle) + height * sin(angle);
    points_[2].y = center.y + width * sin(angle) - height * cos(angle);

    points_[3].x = center.x - width * cos(angle) + height * sin(angle);
    points_[3].y = center.y - width * sin(angle) - height * cos(angle);

    points_[4] = points_[0];
}

void ColliderViewer::draw() const {
    if (drawable_ && !isUIElement_) {

        // lista de fixtures del body
        b2Fixture* f = body_->GetFixtureList();
        int i = 0;
        // recorre todos los fixtures del objeto
        while (f != nullptr) {

            if (f->GetNext() != nullptr)
                std::cout << "Collider con más de una fixture" << endl;

            uint16 layer = f->GetFilterData().categoryBits;
            int posColor = (layer > 0) ? round(log2(layer)) : 8;        // escoge color de dibujado
            // cambia color de dibujado
            SDL_SetRenderDrawColor(renderer_, colors[posColor].r, colors[posColor].g, colors[posColor].b, SDL_ALPHA_OPAQUE);

            (f->GetShape()->GetType() != b2Shape::e_circle) ? // pregunta tipo de collider

                drawRect(i)                                           // collider rectangular
                :                                 
                drawCircle(renderer_, collider_->getRectRender(i).x,   // collider circular
                    collider_->getRectRender(i).y,
                    collider_->getW(i) * PIXELS_PER_METER);

            f = f->GetNext();   // siguiente fixture del body
            i++;
        }
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    }
}

// este algoritmo es bastante r�pido (~500 microsegundos)
void ColliderViewer::drawCircle(SDL_Renderer* renderer, int32_t originX, int32_t originY, int32_t radius) const
{
    b2Vec2 center = { (float)(originX + radius), (float)(originY + radius) };

    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, center.x + x, center.y - y);
        SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
        SDL_RenderDrawPoint(renderer, center.x - x, center.y - y);
        SDL_RenderDrawPoint(renderer, center.x - x, center.y + y);
        SDL_RenderDrawPoint(renderer, center.x + y, center.y - x);
        SDL_RenderDrawPoint(renderer, center.x + y, center.y + x);
        SDL_RenderDrawPoint(renderer, center.x - y, center.y - x);
        SDL_RenderDrawPoint(renderer, center.x - y, center.y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
