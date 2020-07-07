(defun my-zap-to-char (arg char)
  (interactive "*p\ncZap to char: ")
  (kill-region (point)
			   (progn
				 (search-forward
				  (char-to-string char) nil nil arg)
				 (point))))
test

(search-forward "test" nil nil 1)
testtet

