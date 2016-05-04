#ifndef IMAGE_LIBRARY_HPP
#define IMAGE_LIBRARY_HPP

/* A repository for images, which underneath are stored as sf::Textures.
 */



class ImageLibrary
{
private:
  std::map<std::string,sf::Texture> textures;
protected:
public:
  ImageLibrary ();
  virtual ~ImageLibrary ();

  ImageId loadImage (std::string source);

  // Moving is supported, copying is not.
  ImageLibrary (ImageLibrary const &) = delete;
  ImageLibrary (ImageLibrary && other) = default;
  ImageLibrary & operator= (ImageLibrary const &) = delete;
  ImageLibrary & operator= (ImageLibrary && other) = default;
};
#endif//IMAGE_LIBRARY_HPP
