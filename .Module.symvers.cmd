cmd_/home/josh/repos/damn-small-driver/Module.symvers := sed 's/ko$$/o/' /home/josh/repos/damn-small-driver/modules.order | scripts/mod/modpost -m    -o /home/josh/repos/damn-small-driver/Module.symvers -e -i Module.symvers   -T -