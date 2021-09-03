//
//  SwiftDefs.h
//  
//
//  Created by Dmitriy Borovikov on 03.09.2021.
//

#ifndef SwiftDefs_h
#define SwiftDefs_h

#if __has_attribute(enum_extensibility)
# define CLOSED_ENUM_ATTR __attribute__((enum_extensibility(closed)))
# define OPEN_ENUM_ATTR __attribute__((enum_extensibility(open)))
#else
# define CLOSED_ENUM_ATTR
# define OPEN_ENUM_ATTR
#endif

#ifndef NS_ENUM
#define NS_ENUM(_type, _name) enum OPEN_ENUM_ATTR _name : _type _name; enum OPEN_ENUM_ATTR _name : _type
#endif
#ifndef NS_CLOSED_ENUM
#define NS_CLOSED_ENUM(_type, _name) enum CLOSED_ENUM_ATTR _name : _type _name; enum CLOSED_ENUM_ATTR _name : _type
#endif


#if __has_attribute(swift_name)
# define CF_SWIFT_NAME(_name) __attribute__((swift_name(#_name)))
#else
# define CF_SWIFT_NAME(_name)
#endif

#endif
