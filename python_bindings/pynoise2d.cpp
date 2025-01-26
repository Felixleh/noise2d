#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <PerlinNoiseGenerator.h>


namespace py = pybind11;

py::array_t<float> generate(PerlinNoiseGenerator& generator)
{
	py::array_t<float> result({ generator.getHeight(), generator.getWidth() });

	py::buffer_info resultsBuffer = result.request();
	float* resultsPtr = static_cast<float*>(resultsBuffer.ptr);
	std::span<float> span(resultsPtr, generator.getHeight() * generator.getWidth());
	Image image(span, generator.getHeight(), generator.getWidth());

	generator.generate(image);

	return result;
}


PYBIND11_MODULE(pynoise2d, m)
{
    py::class_<PerlinNoiseGenerator>(m, "PerlinNoiseGenerator")
		.def(py::init<int, int, int, float>(), py::arg("height"), py::arg("width"), py::arg("octaves"), py::arg("scale"))
		.def("generate", &generate);
}