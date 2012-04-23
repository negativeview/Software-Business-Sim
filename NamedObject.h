#ifndef NAMED_OBJECT_H
#define NAMED_OBJECT_H

class NamedObject {
	public:
		NamedObject(const char *tag, const char *fullName);
		~NamedObject();

		const char *getFullName();
		const char *getTag();
	protected:
	private:
		char *_tag;
		char *_fullName;
};

#endif