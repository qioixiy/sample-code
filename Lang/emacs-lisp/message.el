(message "this message appears in the echo area!")
(message "the name of this buffer is : %s." (buffer-name))
(message "the calue of fill-column is %d." fill-column)
(message "there are %d %s in the office!"
		 (- fill-column 14) "pink elephants")
(message "he saw %d %s"
		 (- fill-column 34)
		 (concat "red "
				 (substring
				  "the quick brown foxes jumped." 16 21)
				 " leaping."))
