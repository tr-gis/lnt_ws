
(cl:in-package :asdf)

(defsystem "lnt_packet-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "lnt_packet" :depends-on ("_package_lnt_packet"))
    (:file "_package_lnt_packet" :depends-on ("_package"))
  ))