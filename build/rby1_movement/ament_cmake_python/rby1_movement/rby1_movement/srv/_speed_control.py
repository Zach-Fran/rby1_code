# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rby1_movement:srv/SpeedControl.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SpeedControl_Request(type):
    """Metaclass of message 'SpeedControl_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('rby1_movement')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rby1_movement.srv.SpeedControl_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__speed_control__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__speed_control__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__speed_control__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__speed_control__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__speed_control__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SpeedControl_Request(metaclass=Metaclass_SpeedControl_Request):
    """Message class 'SpeedControl_Request'."""

    __slots__ = [
        '_speed_input',
    ]

    _fields_and_field_types = {
        'speed_input': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.speed_input = kwargs.get('speed_input', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.speed_input != other.speed_input:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def speed_input(self):
        """Message field 'speed_input'."""
        return self._speed_input

    @speed_input.setter
    def speed_input(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'speed_input' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'speed_input' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._speed_input = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SpeedControl_Response(type):
    """Metaclass of message 'SpeedControl_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('rby1_movement')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rby1_movement.srv.SpeedControl_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__speed_control__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__speed_control__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__speed_control__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__speed_control__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__speed_control__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SpeedControl_Response(metaclass=Metaclass_SpeedControl_Response):
    """Message class 'SpeedControl_Response'."""

    __slots__ = [
        '_success',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.success != other.success:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value


class Metaclass_SpeedControl(type):
    """Metaclass of service 'SpeedControl'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('rby1_movement')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rby1_movement.srv.SpeedControl')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__speed_control

            from rby1_movement.srv import _speed_control
            if _speed_control.Metaclass_SpeedControl_Request._TYPE_SUPPORT is None:
                _speed_control.Metaclass_SpeedControl_Request.__import_type_support__()
            if _speed_control.Metaclass_SpeedControl_Response._TYPE_SUPPORT is None:
                _speed_control.Metaclass_SpeedControl_Response.__import_type_support__()


class SpeedControl(metaclass=Metaclass_SpeedControl):
    from rby1_movement.srv._speed_control import SpeedControl_Request as Request
    from rby1_movement.srv._speed_control import SpeedControl_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
