#ifndef IMAGE_LIBRARY_HPP
#define IMAGE_LIBRARY_HPP

/* A repository for images, which underneath are stored as sf::Textures.
 */



class ImageLibrary
{
private:
  std::map<std::string, sf::Texture *> textures;
  // Pointers to all of the currently loaded textures.
  // The instances themselves will move around.
protected:
public:
  ImageLibrary ();
  virtual ~ImageLibrary ();

  ImageId loadImage (std::string source);
  sf::Texture & getImage (ImageId);

  sf::Texture & getTexture (std::string const & name);
  /* Get a texture with a given name.
   * Params: The name of the texture as a string.
   * Effect: Loads texture if it is not loaded already.
   * Return: Reference to Texture.
   * Throws: Some exception if the texture cannot be loaded.
   */

  // Moving is supported, copying is not.
  ImageLibrary (ImageLibrary const &) = delete;
  ImageLibrary (ImageLibrary && other) = default;
  ImageLibrary & operator= (ImageLibrary const &) = delete;
  ImageLibrary & operator= (ImageLibrary && other) = default;
};
#endif//IMAGE_LIBRARY_HPP
