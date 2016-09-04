(setq trees `(pine fir oak maple)
	  herbivores `(gazelle antelope zebra))

trees
herbivores
(message "%s ,%s" trees herbivores)

;;counter
(setq counter 0)
(setq counter (+ counter 1))
counter

test
(+ test 2)
;;counter-2
(setq counter-2 0)
(setq counter-2 (+ counter-2 2))
counter-2

(setq getvalue 0)
(setq getvalue (+ getvalue 1))
getvalue
temp


(buffer-name)
(buffer-file-name)
(current-buffer)
(other-buffer)
(switch-to-buffer (other-buffer))
(switch-to-buffer (current-buffer))

(set-buffer (other-buffer))

(buffer-size)
(point)
(point-min)
(point-max)
(defun print-point()
  (message "point=%d" (point)))
(print-point)

(defun file-des()
  (message "buffer-name:%s buffer-size:%d point:%d point-max:%d"
		   (buffer-name)
		   (buffer-size)
		   (point)
		   (point-max)))

(file-des)
