; Auto-generated. Do not edit!


(cl:in-package lnt_ik-srv)


;//! \htmlinclude lnt_ik-request.msg.html

(cl:defclass <lnt_ik-request> (roslisp-msg-protocol:ros-message)
  ((values
    :reader values
    :initarg :values
    :type (cl:vector cl:float)
   :initform (cl:make-array 6 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass lnt_ik-request (<lnt_ik-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <lnt_ik-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'lnt_ik-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lnt_ik-srv:<lnt_ik-request> is deprecated: use lnt_ik-srv:lnt_ik-request instead.")))

(cl:ensure-generic-function 'values-val :lambda-list '(m))
(cl:defmethod values-val ((m <lnt_ik-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lnt_ik-srv:values-val is deprecated.  Use lnt_ik-srv:values instead.")
  (values m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <lnt_ik-request>) ostream)
  "Serializes a message object of type '<lnt_ik-request>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'values))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <lnt_ik-request>) istream)
  "Deserializes a message object of type '<lnt_ik-request>"
  (cl:setf (cl:slot-value msg 'values) (cl:make-array 6))
  (cl:let ((vals (cl:slot-value msg 'values)))
    (cl:dotimes (i 6)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<lnt_ik-request>)))
  "Returns string type for a service object of type '<lnt_ik-request>"
  "lnt_ik/lnt_ikRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'lnt_ik-request)))
  "Returns string type for a service object of type 'lnt_ik-request"
  "lnt_ik/lnt_ikRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<lnt_ik-request>)))
  "Returns md5sum for a message object of type '<lnt_ik-request>"
  "a1a2eac268981f596d714f7568cb7d14")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'lnt_ik-request)))
  "Returns md5sum for a message object of type 'lnt_ik-request"
  "a1a2eac268981f596d714f7568cb7d14")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<lnt_ik-request>)))
  "Returns full string definition for message of type '<lnt_ik-request>"
  (cl:format cl:nil "float32[6] values~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'lnt_ik-request)))
  "Returns full string definition for message of type 'lnt_ik-request"
  (cl:format cl:nil "float32[6] values~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <lnt_ik-request>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'values) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <lnt_ik-request>))
  "Converts a ROS message object to a list"
  (cl:list 'lnt_ik-request
    (cl:cons ':values (values msg))
))
;//! \htmlinclude lnt_ik-response.msg.html

(cl:defclass <lnt_ik-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass lnt_ik-response (<lnt_ik-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <lnt_ik-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'lnt_ik-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lnt_ik-srv:<lnt_ik-response> is deprecated: use lnt_ik-srv:lnt_ik-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <lnt_ik-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lnt_ik-srv:result-val is deprecated.  Use lnt_ik-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <lnt_ik-response>) ostream)
  "Serializes a message object of type '<lnt_ik-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'result) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <lnt_ik-response>) istream)
  "Deserializes a message object of type '<lnt_ik-response>"
    (cl:setf (cl:slot-value msg 'result) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<lnt_ik-response>)))
  "Returns string type for a service object of type '<lnt_ik-response>"
  "lnt_ik/lnt_ikResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'lnt_ik-response)))
  "Returns string type for a service object of type 'lnt_ik-response"
  "lnt_ik/lnt_ikResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<lnt_ik-response>)))
  "Returns md5sum for a message object of type '<lnt_ik-response>"
  "a1a2eac268981f596d714f7568cb7d14")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'lnt_ik-response)))
  "Returns md5sum for a message object of type 'lnt_ik-response"
  "a1a2eac268981f596d714f7568cb7d14")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<lnt_ik-response>)))
  "Returns full string definition for message of type '<lnt_ik-response>"
  (cl:format cl:nil "bool result~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'lnt_ik-response)))
  "Returns full string definition for message of type 'lnt_ik-response"
  (cl:format cl:nil "bool result~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <lnt_ik-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <lnt_ik-response>))
  "Converts a ROS message object to a list"
  (cl:list 'lnt_ik-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'lnt_ik)))
  'lnt_ik-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'lnt_ik)))
  'lnt_ik-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'lnt_ik)))
  "Returns string type for a service object of type '<lnt_ik>"
  "lnt_ik/lnt_ik")