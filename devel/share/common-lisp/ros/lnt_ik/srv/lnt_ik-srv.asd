
(cl:in-package :asdf)

(defsystem "lnt_ik-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "lnt_ik" :depends-on ("_package_lnt_ik"))
    (:file "_package_lnt_ik" :depends-on ("_package"))
  ))