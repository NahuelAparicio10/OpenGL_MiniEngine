# [OPEN GL] Mini Engine

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-5586A4?style=for-the-badge&logo=opengl&logoColor=white)
![GLSL](https://img.shields.io/badge/GLSL-5566AA?style=for-the-badge&logo=opengl&logoColor=white)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

**GOAL** 

Develop a small rendering engine in C++ using OpenGL that integrates multiple techniques learned throughout the course, with a focus on real-time lighting. The final project had to demonstrate features such as a day/night cycle, ambient lighting, and dynamic flashlight illumination.

**How I resolved it**

I structured the engine using a modular component-based approach organizing the code into managers (for objects, maps, programs, and time) and core components (Transform, MeshRenderer, Material, Texture). I implemented custom shaders (vertex, fragment, and geometry) to handle lighting effects such as directional sun/moon cycles and spotlights for the flashlight. The camera and input manager allowed free navigation in the scene, while the procedural map generation system ensured variety on each run.

**What I learned**

I learned how to architect a small graphics engine using OpenGL, separating responsibilities into reusable components and managers. I deepened my understanding of GLSL shader programming, especially for dynamic lighting, and practiced designing a clean codebase similar to an ECS structure which I really like from Unity projects I made before. This project also taught me how to integrate multiple rendering feature such as camera, input, textures, and shaders into a cohesive system.

```markdown
 📞 Contact

Nahuel Aparicio Del Blanco

- GitHub: https://github.com/NahuelAparicio10
- Email: nahuel.ap.code@gmail.com
- LinkedIn: https://www.linkedin.com/in/nahuel-aparicio-del-blanco
