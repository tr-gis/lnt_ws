; Auto-generated. Do not edit!


(cl:in-package lnt_packet-msg)


;//! \htmlinclude lnt_packet.msg.html

(cl:defclass <lnt_packet> (roslisp-msg-protocol:ros-message)
  ((packet_code
    :reader packet_code
    :initarg :packet_code
    :type cl:fixnum
    :initform 0)
   (values
    :reader values
    :initarg :values
    :type (cl:vector cl:float)
   :initform (cl:make-array 6 :element-type 'cl:float :initial-element 0.0))
   (eff_mode
    :reader eff_mode
    :initarg :eff_mode
    :type cl:fixnum
    :initform 0))
)

(cl:defclass lnt_packet (<lnt_packet>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <lnt_packet>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'lnt_packet)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lnt_packet-msg:<lnt_packet> is deprecated: use lnt_packet-msg:lnt_packet instead.")))

(cl:ensure-generic-function 'packet_code-val :lambda-list '(m))
(cl:defmethod packet_code-val ((m <lnt_packet>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lnt_packet-msg:packet_code-val is deprecated.  Use lnt_packet-msg:packet_code instead.")
  (packet_code m))

(cl:ensure-generic-function 'values-val :lambda-list '(m))
(cl:defmethod values-val ((m <lnt_packet>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lnt_packet-msg:values-val is deprecated.  Use lnt_packet-msg:values instead.")
  (values m))

(cl:ensure-generic-function 'eff_mode-val :lambda-list '(m))
(cl:defmethod eff_mode-val ((m <lnt_packet>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lnt_packet-msg:eff_mode-val is deprecated.  Use lnt_packet-msg:eff_mode instead.")
  (eff_mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <lnt_packet>) ostream)
  "Serializes a message object of type '<lnt_packet>"
  (cl:let* ((signed (cl:slot-value msg 'packet_code)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'values))
  (cl:let* ((signed (cl:slot-value msg 'eff_mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <lnt_packet>) istream)
  "Deserializes a message object of type '<lnt_packet>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'packet_code) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  (cl:setf (cl:slot-value msg 'values) (cl:make-array 6))
  (cl:let ((vals (cl:slot-value msg 'values)))
    (cl:dotimes (i 6)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'eff_mode) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<lnt_packet>)))
  "Returns string type for a message object of type '<lnt_packet>"
  "lnt_packet/lnt_packet")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'lnt_packet)))
  "Returns string type for a message object of type 'lnt_packet"
  "lnt_packet/lnt_packet")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<lnt_packet>)))
  "Returns md5sum for a message object of type '<lnt_packet>"
  "f9c87db58664bf6126cb6c2b6c55b3f5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'lnt_packet)))
  "Returns md5sum for a message object of type 'lnt_packet"
  "f9c87db58664bf6126cb6c2b6c55b3f5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<lnt_packet>)))
  "Returns full string definition for message of type '<lnt_packet>"
  (cl:format cl:nil "int8 packet_code~%float32[6] values~%int8 eff_mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'lnt_packet)))
  "Returns full string definition for message of type 'lnt_packet"
  (cl:format cl:nil "int8 packet_code~%float32[6] values~%int8 eff_mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <lnt_packet>))
  (cl:+ 0
     1
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'values) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <lnt_packet>))
  "Converts a ROS message object to a list"
  (cl:list 'lnt_packet
    (cl:cons ':packet_code (packet_code msg))
    (cl:cons ':values (values msg))
    (cl:cons ':eff_mode (eff_mode msg))
))
