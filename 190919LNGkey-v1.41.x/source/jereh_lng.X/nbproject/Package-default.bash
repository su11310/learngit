�}�gz �   �&��M�߷� 0��3.�IC[ij�2�i�G+�Ռ�(86�y�r&��?!�� 1������2�!�*5�v�ꆧk�w��K:����k�=���u�ؚs4��6.c��7�i���B|h�L��h�J��7����'�(HWۤצa^�L�re�È���p��R�����c%+h-���Q�ѓ��OD�n��2���
��rH;*1�6���X����,v�Xс�,��U�P#���\;$�[%[dIK��u�W���[��Y�m�NlkY��rFhm�2�PuD����Pm���,�s}%����G��.�k^djx�MD��L���A b�QD��d��B��D�;�>%l��Z���>`ͳ�;|�I9!��X+#��0���;mtY���jNi6Y�%R��DG�<�E�'�ƨ�t�:[ݰ�Z�<�"����p;��ް;sT%�M������d�a[d�k�ڄh����J�����F��&�	6��BY�~�ɹl�(p>�8���4�R}����XC&3h
$��N�f$b@R5_��Q#"���s`�����̑��Z*P��=��.���ܗ�xX#�
�0za}N�uG�BU&dSX{á�O�c謍=S��!	�������!,bk>���V�r�לK޺ ����_wD�k5����x��O��TW;��1ֿ�p�1b���Ǻ����hQ7��'�P��-��	MK����0ZS=4F���-��,^ո`)�����+ę�]�����M���g�;��D^�U�"��Qwv[$�/��lH~�&�Q���+��w����_�`#z�2u ����}��
�����+�XJ�h��9���p�s}{+���h\ �s�~��O'�l����sEfA������{�=� d�d���������lf�~����i��D5����]���Q\�7ٌsn�⿨p_D�<�>w0 &�4��.�>[Bs�V���MYW�U���L,�«���1W� ���.����ory ${TMPDIR}/jerehlng.x/bin
copyFileToTmpDir "${OUTPUT_PATH}" "${TMPDIR}/${PACKAGE_TOP_DIR}bin/${OUTPUT_BASENAME}" 0755


# Generate tar file
cd "${TOP}"
rm -f ${CND_DISTDIR}/${CND_CONF}/package/jerehlng.x.tar
cd ${TMPDIR}
tar -vcf ../../../../${CND_DISTDIR}/${CND_CONF}/package/jerehlng.x.tar *
checkReturnCode

# Cleanup
cd "${TOP}"
rm -rf ${TMPDIR}
