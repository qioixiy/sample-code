(if 4
	`true
  `false)

(if nil
	`true
  `false)

(message "the result is %s" ;the result is t
		 (> 5 4))
(message "the result is %s" ;the result is nil
		 (< 5 4))
