#include "SpotLight.h"

SpotLight::SpotLight()
{
	_cutOff = 30.0;
	_exponent = 2.0;
}

void SpotLight::ProjectLight()
{
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHT0);

    // Configuración de las propiedades de la luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // w debe ser 1.0 para spotlights
    glm::vec3 pos = Camera::GetInstance().GetPosition();
    GLfloat position[] = { pos.x, pos.y, pos.z, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, _cutOff);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, _exponent);

    glm::vec3 dir = Camera::GetInstance().getVectorFront();
    GLfloat direction[] = { dir.x, dir.y, dir.z };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
}


const std::type_index SpotLight::GetType()
{
	return typeid(SpotLight);
}