// Generated by gencpp from file lnt_packet/lnt_packet.msg
// DO NOT EDIT!


#ifndef LNT_PACKET_MESSAGE_LNT_PACKET_H
#define LNT_PACKET_MESSAGE_LNT_PACKET_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace lnt_packet
{
template <class ContainerAllocator>
struct lnt_packet_
{
  typedef lnt_packet_<ContainerAllocator> Type;

  lnt_packet_()
    : packet_code(0)
    , values()
    , eff_mode(0)  {
      values.assign(0.0);
  }
  lnt_packet_(const ContainerAllocator& _alloc)
    : packet_code(0)
    , values()
    , eff_mode(0)  {
  (void)_alloc;
      values.assign(0.0);
  }



   typedef int8_t _packet_code_type;
  _packet_code_type packet_code;

   typedef boost::array<float, 6>  _values_type;
  _values_type values;

   typedef int8_t _eff_mode_type;
  _eff_mode_type eff_mode;




  typedef boost::shared_ptr< ::lnt_packet::lnt_packet_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::lnt_packet::lnt_packet_<ContainerAllocator> const> ConstPtr;

}; // struct lnt_packet_

typedef ::lnt_packet::lnt_packet_<std::allocator<void> > lnt_packet;

typedef boost::shared_ptr< ::lnt_packet::lnt_packet > lnt_packetPtr;
typedef boost::shared_ptr< ::lnt_packet::lnt_packet const> lnt_packetConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::lnt_packet::lnt_packet_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::lnt_packet::lnt_packet_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace lnt_packet

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'lnt_packet': ['/home/raj/lnt_ws/src/lnt_packet/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::lnt_packet::lnt_packet_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::lnt_packet::lnt_packet_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::lnt_packet::lnt_packet_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::lnt_packet::lnt_packet_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::lnt_packet::lnt_packet_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::lnt_packet::lnt_packet_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::lnt_packet::lnt_packet_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f9c87db58664bf6126cb6c2b6c55b3f5";
  }

  static const char* value(const ::lnt_packet::lnt_packet_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf9c87db58664bf61ULL;
  static const uint64_t static_value2 = 0x26cb6c2b6c55b3f5ULL;
};

template<class ContainerAllocator>
struct DataType< ::lnt_packet::lnt_packet_<ContainerAllocator> >
{
  static const char* value()
  {
    return "lnt_packet/lnt_packet";
  }

  static const char* value(const ::lnt_packet::lnt_packet_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::lnt_packet::lnt_packet_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int8 packet_code\n\
float32[6] values\n\
int8 eff_mode\n\
";
  }

  static const char* value(const ::lnt_packet::lnt_packet_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::lnt_packet::lnt_packet_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.packet_code);
      stream.next(m.values);
      stream.next(m.eff_mode);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct lnt_packet_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::lnt_packet::lnt_packet_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::lnt_packet::lnt_packet_<ContainerAllocator>& v)
  {
    s << indent << "packet_code: ";
    Printer<int8_t>::stream(s, indent + "  ", v.packet_code);
    s << indent << "values[]" << std::endl;
    for (size_t i = 0; i < v.values.size(); ++i)
    {
      s << indent << "  values[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.values[i]);
    }
    s << indent << "eff_mode: ";
    Printer<int8_t>::stream(s, indent + "  ", v.eff_mode);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LNT_PACKET_MESSAGE_LNT_PACKET_H
