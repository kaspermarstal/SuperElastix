#ifndef AnyFileReader_h
#define AnyFileReader_h

#include "itkImageSource.h"
#include "itkImageToImageFilter.h"
#include "itkMesh.h"

/**
* \class selxFileReaderDecorator
* \brief A base class to handle any file reader that derives from this class.
*/

namespace selx
{

class AnyFileReader : public itk::ProcessObject
{
public:

  /** Standard ITK typedefs. */
  typedef AnyFileReader                   Self;
  typedef itk::ProcessObject Superclass;
  typedef itk::SmartPointer< Self >       Pointer;
  typedef itk::SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  //itkNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro(Self, itk::ProcessObject);
  //typedef itk::DataObject InputDataType;
  typedef itk::DataObject OutputDataType;
  //typedef itk::DataObject DataObject;

  virtual void SetFileName(const std::string) = 0 ;
  /** SetInput accepts any input data as long as it is derived from itk::DataObject */
  //void SetInput(const DataObjectIdentifierType&, InputDataType*) ITK_OVERRIDE;
  
  /** Non type-specific GetOutput */
  virtual OutputDataType * GetOutput() = 0 ;

  virtual void Update(void) = 0 ;

  /** GetOutput tries dynamic cast to required output type */
  //template<typename ReturnType>
  //ReturnType* GetOutput(const DataObjectIdentifierType&);

protected:

  //AnyFileReader(void) {};
  //~AnyFileReader(void) {};

  //virtual void GenerateData(void) ITK_OVERRIDE;
  //virtual void GenerateOutputInformation(void) ITK_OVERRIDE;

};

} // namespace elx


#endif // AnyFileReader_h
