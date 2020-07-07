(defun mark-whole-buffer ()
  "put point at beginning and mark at end of buffer."
  (interactive)
  (push-mark (point))
  (push-mark (point-max))
  (message-box "ok")
  (goto-char (point-min)))

(mark-whole-buffer)
