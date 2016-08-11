////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2016
//
// example of FBX file decoder and encoder
//
////////////////////////////////////////////////////////////////////////////////

#include <meshutils/mesh.hpp>
#include <meshutils/scene.hpp>
#include <meshutils/decoders/fbx_decoder.hpp>
#include <meshutils/encoders/fbx_encoder.hpp>

int main(int argc, char **argv) {
  const char *filename = nullptr;
  for (int i = 1; i != argc; ++i) {
    const char *arg = argv[i];
    if (arg[0] == '-') {
      printf("invalid argument %s\n", arg);
    } else {
      filename = arg;
    }
  }

  if (filename == nullptr) {
    filename = CMAKE_SOURCE "/examples/data/cube.fbx";
  }

  meshutils::fbx_decoder decoder;

  meshutils::scene scene;
  if (!decoder.loadScene<meshutils::color_mesh>(scene, filename)) {
    std::cerr << "uable to open file " << filename << "\n";
    return 1;
  }

  meshutils::fbx_encoder encoder;
  auto bytes = encoder.saveScene(scene);

  std::ofstream("out.fbx", std::ios::binary).write((char*)bytes.data(), bytes.size());
}

