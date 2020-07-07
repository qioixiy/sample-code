(defun my-copy-region-as-kill (beg end)
  "Save the region as if killed, but don`t kill it."
  (interactive "r")
  (if (eq last-command `kill-region)
	  (kill-append (buffer-substring beg end) (< end beg))
	(setq kill-ring
		  (cons (buffer-substring beg end) kill-ring))
	(if (> (length kill-ring) kill-ring-max)
		(setcdr (nthcdr (1- kill-ring-max) kill-ring) nil)))
  (setq this-command `kill-region)
  (setq kill-ring-yank-pointer kill-ring))
(my-common-mode-auto-pair)
(1- 4)

this-command
last-command
