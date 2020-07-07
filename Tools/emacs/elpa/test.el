
;; Packages Repositories
(when (>= emacs-major-version 24)
  (require 'package)
  
  ;; has most packages, and updated daily
  (add-to-list 'package-archives
	       '("melpa" . "http://melpa.org/packages/") t)
  ;; More extensive number of packages
  (add-to-list 'package-archives
	       '("marmalade" . "http://marmalade-repo.org/packages/") t)
  ;; Emacs users in China mainland
  (add-to-list 'package-archives
	       '("popkit" . "http://elpa.popkit.org/packages/"))
  (package-initialize))

;; (list-packages)
