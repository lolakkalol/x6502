case BCC_REL:
    s1 = NEXT_BYTE(m);
    if (!get_flag(m, FLAG_CARRY)) {
        branch_offset = s1;
    }
    break;

case BCS_REL:
    s1 = NEXT_BYTE(m);
    if (get_flag(m, FLAG_CARRY)) {
        branch_offset = s1;
    }
    break;

case BEQ_REL:
    s1 = NEXT_BYTE(m);
    if (get_flag(m, FLAG_ZERO)) {
        branch_offset = s1;
    }
    break;

case BMI_REL:
    s1 = NEXT_BYTE(m);
    if (get_flag(m, FLAG_NEGATIVE)) {
        branch_offset = s1;
    }
    break;

case BNE_REL:
    s1 = NEXT_BYTE(m);
    if (!get_flag(m, FLAG_ZERO)) {
        branch_offset = s1;
    }
    break;

case BPL_REL:
    s1 = NEXT_BYTE(m);
    if (!get_flag(m, FLAG_NEGATIVE)) {
        branch_offset = s1;
    }
    break;

case BVC_REL:
    s1 = NEXT_BYTE(m);
    if (!get_flag(m, FLAG_OVERFLOW)) {
        branch_offset = s1;
    }
    break;

case BVS_REL:
    s1 = NEXT_BYTE(m);
    if (get_flag(m, FLAG_OVERFLOW)) {
        branch_offset = s1;
    }
    break;

case BRA:
    branch_offset = NEXT_BYTE(m);
    break;

case BBR0:
    s1 = NEXT_BYTE(m);
    if(!(s1 & 0x01)) {
        branch_offset = s1;
    }
    break;

case BBR1:
    s1 = NEXT_BYTE(m);
    if(!(s1 & 0x02)) {
        branch_offset = s1;
    }
    break;

case BBR2:
    s1 = NEXT_BYTE(m);
    if(!(s1 & 0x04)) {
        branch_offset = s1;
    }
    break;

case BBR3:
    s1 = NEXT_BYTE(m);
    if(!(s1 & 0x08)) {
        branch_offset = s1;
    }
    break;

case BBR4:
    s1 = NEXT_BYTE(m);
    if(!(s1 & 0x10)) {
        branch_offset = s1;
    }
    break;

case BBR5:
    s1 = NEXT_BYTE(m);
    if(!(s1 & 0x20)) {
        branch_offset = s1;
    }
    break;

case BBR6:
    s1 = NEXT_BYTE(m);
    if(!(s1 & 0x40)) {
        branch_offset = s1;
    }
    break;

case BBR7:
    s1 = NEXT_BYTE(m);
    if(!(s1 & 0x80)) {
        branch_offset = s1;
    }
    break;

case BBS0:
    s1 = NEXT_BYTE(m);
    if(s1 & 0x01) {
        branch_offset = s1;
    }
    break;

case BBS1:
    s1 = NEXT_BYTE(m);
    if(s1 & 0x20) {
        branch_offset = s1;
    }
    break;

case BBS2:
    s1 = NEXT_BYTE(m);
    if(s1 & 0x04) {
        branch_offset = s1;
    }
    break;

case BBS3:
    s1 = NEXT_BYTE(m);
    if(s1 & 0x08) {
        branch_offset = s1;
    }
    break;

case BBS4:
    s1 = NEXT_BYTE(m);
    if(s1 & 0x01) {
        branch_offset = s1;
    }
    break;

case BBS5:
    s1 = NEXT_BYTE(m);
    if(s1 & 0x20) {
        branch_offset = s1;
    }
    break;

case BBS6:
    s1 = NEXT_BYTE(m);
    if(s1 & 0x40) {
        branch_offset = s1;
    }
    break;

case BBS7:
    s1 = NEXT_BYTE(m);
    if(s1 & 0x80) {
        branch_offset = s1;
    }
    break;
