#!/bin/bash
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 2048 -soundhw pcspk,sb16,es1370,adlib
