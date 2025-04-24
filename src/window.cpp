#include <glad/glad.h> //should always be at the top, contains the required OpenGL headers 
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	//the first param of glfwWindowHint is from an enum and the second is an integer which sets value of option. In partiuclar, this sets which version of GLFW we are using, 4.5
	glfwInit(); //initialize GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //this, and the following two lines, are config details for GLFW; reference - www.glfw.org/docs/latest/window.html#window_hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//simply creates a glfw window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World!", NULL, NULL); //width, height, name of window
	if (window == NULL)
	{
		cout << "Failed to create GLFW window." << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // tells GLFW to make the context of window main context on the current thread

	//GLAD initalization, manages function pointers for OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD." << endl;
		return -1;
	}

	glViewport(0, 0, 800, 600); // defines size of the rendering window. First two define lower left and last two upper right
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// render loop, keep running untill GLFW has been told to stop
	while (!glfwWindowShouldClose) { // checks if GLFW has been instructed to close, true meaning close
		glfwSwapBuffers(window); // swaps color buffers every iteration of this loop
		glfwPollEvents(); // checks for any events being triggered, updates state of window, and calls callback methods
	}

	glfwTerminate(); // cleans up any remaining resources
	return 0;
}

// this routine is able resize the window whenever the user resizes the window; callback functions await user updates
// there exist other callback functions as well; controller input for instance
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*
	Some notes...

	Windowing applications apply a double buffer for rendering, such as the glfwSwapBuffers routine. This is because the resulting output image is not drawn immediately but rather
	pixel-by-pixel left to right. To prevent this, two buffers are used. The front buffer contains the final image and the back buffer is where the next image state is rendered. 
	Once this next image is rendered, it is then pushed to the front. 
*/