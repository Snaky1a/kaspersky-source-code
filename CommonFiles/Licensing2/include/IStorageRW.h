/* Generated by Together */

#ifndef ISTORAGERW_H
#define ISTORAGERW_H

namespace KasperskyLicensing {

/** @interface */
class IStorageRW : public IStorageR
{
public:

	/**
	 * adds object to storage
	 */
	virtual void StoreObject(const IObjectImage& obj) = 0;

	/**
	 * removes object from storage by given name
	 */
	virtual void RemoveObject(const char_t* name) = 0;

private:

	/** @link dependency
	 * @stereotype use*/
	/*# IObjectImage lnkIStoredObject; */
};

} // namespace KasperskyLicensing

#endif // ISTORAGERW_H
