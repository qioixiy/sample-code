(if (> 5 4)
	(message "5 is greater than 4!"))

(defun type-of-animal (characteristic)
  "print message in echo area epending on characteristic.
if the characteristic is the symbol 'fierce',
the warn of a tiger."
  (if (equal characteristic `fierce)
	  (message "it is a tiger!")))
(type-of-animal `fierce)
(type-of-animal `zebra)

(if (string= (int-to-string 19)
			 (substring (emacs-version) 10 12))
	(message "this is version 19 emacs")
  (message "this is not version 19 emacs"))

(defun print-ascii(param)
  (message "%c" param))
(print-ascii 40)

(mark-whole-buffer)
