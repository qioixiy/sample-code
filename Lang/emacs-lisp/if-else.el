(if (> 5 4)
	(message "5 is greater than 4!")
  (message  "4 is greater than 5!"))

(defun type-of-animal (characteristic)
  "print message in echo area epending on characteristic.
if the characteristic is the symbol 'fierce',
the warn of a tiger;
else say it`s not fierce."
  (if (equal characteristic `fierce)
	  (message "it`s a tiger!")
	(message "it`s not fierce!")))
(type-of-animal `fierce)
(type-of-animal `zebra)



