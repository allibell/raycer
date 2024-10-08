#include "raycer/textures/Texture.h"
#include "core/Color.h"

#include <memory>

namespace raycer {
    class TextureMapping2D;

    class CheckerBoardTexture : public Texturec {
        public:
            inline explicit CheckerBoardTexture(TextureMapping2D* mapping)
                : m_mapping(mapping),
                m_brightTexture(nullptr),
                m_darkTexture(nullptr)
        {
        }

            inline explicit CheckerBoardTexture(TextureMapping2D* mapping, std::shared_ptr<Texturec> brightTexture, std::shared_ptr<Texturec> darkTexture)
                : m_mapping(mapping),
                m_brightTexture(brightTexture),
                m_darkTexture(darkTexture)
        {
        }

            inline std::shared_ptr<Texturec> brightTexture() const {
                return m_brightTexture;
            }

            inline void setBrightTexture(std::shared_ptr<Texturec> color) {
                m_brightTexture = color;
            }

            inline std::shared_ptr<Texturec> darkTexture() const {
                return m_darkTexture;
            }

            inline void setDarkTexture(std::shared_ptr<Texturec> color) {
                m_darkTexture = color;
            }

            virtual Colord evaluate(const Rayd& ray, const HitPoint& hitPoint) const;

        private:
            TextureMapping2D* m_mapping;
            std::shared_ptr<Texturec> m_brightTexture;
            std::shared_ptr<Texturec> m_darkTexture;
    };
}
