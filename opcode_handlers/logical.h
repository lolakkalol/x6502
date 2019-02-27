case AND_IMM:
    m->ac &= NEXT_BYTE(m);
    set_flags(m, m->ac);
    break;

case AND_ZP:
    m->ac &= m->mem[NEXT_BYTE(m)];
    set_flags(m, m->ac);
    break;

case AND_ZPX:
    m->ac &= m->mem[ZP(NEXT_BYTE(m) + m->x)];
    set_flags(m, m->ac);
    break;

case AND_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac &= m->mem[mem_abs(arg1, arg2, 0)];
    set_flags(m, m->ac);
    break;

case AND_ABX:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac &= m->mem[mem_abs(arg1, arg2, m->x)];
    set_flags(m, m->ac);
    break;

case AND_ABY:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac &= m->mem[mem_abs(arg1, arg2, m->y)];
    set_flags(m, m->ac);
    break;

case AND_INX:
    m->ac &= m->mem[mem_indexed_indirect(m, NEXT_BYTE(m), m->x)];
    set_flags(m, m->ac);
    break;

case AND_INY:
    m->ac &= m->mem[mem_indirect_index(m, NEXT_BYTE(m), m->y)];
    set_flags(m, m->ac);
    break;

case EOR_IMM:
    m->ac ^= NEXT_BYTE(m);
    set_flags(m, m->ac);
    break;

case EOR_ZP:
    m->ac ^= m->mem[NEXT_BYTE(m)];
    set_flags(m, m->ac);
    break;

case EOR_ZPX:
    m->ac ^= m->mem[ZP(NEXT_BYTE(m) + m->x)];
    set_flags(m, m->ac);
    break;

case EOR_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac ^= m->mem[mem_abs(arg1, arg2, 0)];
    set_flags(m, m->ac);
    break;

case EOR_ABX:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac ^= m->mem[mem_abs(arg1, arg2, m->x)];
    set_flags(m, m->ac);
    break;

case EOR_ABY:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac ^= m->mem[mem_abs(arg1, arg2, m->y)];
    set_flags(m, m->ac);
    break;

case EOR_INX:
    m->ac ^= m->mem[mem_indexed_indirect(m, NEXT_BYTE(m), m->x)];
    set_flags(m, m->ac);
    break;

case EOR_INY:
    m->ac ^= m->mem[mem_indirect_index(m, NEXT_BYTE(m), m->y)];
    set_flags(m, m->ac);
    break;

case ORA_IMM:
    m->ac |= NEXT_BYTE(m);
    set_flags(m, m->ac);
    break;

case ORA_ZP:
    m->ac |= m->mem[NEXT_BYTE(m)];
    set_flags(m, m->ac);
    break;

case ORA_ZPX:
    m->ac |= m->mem[ZP(NEXT_BYTE(m) + m->x)];
    set_flags(m, m->ac);
    break;

case ORA_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac |= m->mem[mem_abs(arg1, arg2, 0)];
    set_flags(m, m->ac);
    break;

case ORA_ABX:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac |= m->mem[mem_abs(arg1, arg2, m->x)];
    set_flags(m, m->ac);
    break;

case ORA_ABY:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac |= m->mem[mem_abs(arg1, arg2, m->y)];
    set_flags(m, m->ac);
    break;

case ORA_INX:
    m->ac |= m->mem[mem_indexed_indirect(m, NEXT_BYTE(m), m->x)];
    set_flags(m, m->ac);
    break;

case ORA_INY:
    m->ac |= m->mem[mem_indirect_index(m, NEXT_BYTE(m), m->y)];
    set_flags(m, m->ac);
    break;

case BIT_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    t1 = m->mem[mem_abs(arg1, arg2, 0)];
    set_flag(m, FLAG_ZERO, !(t1 & m->ac));
    set_flag(m, FLAG_OVERFLOW, t1 & 0x40);
    set_flag(m, FLAG_NEGATIVE, t1 & 0x80);
    break;

case BIT_ZP:
    t1 = m->mem[NEXT_BYTE(m)];
    set_flag(m, FLAG_ZERO, !(t1 & m->ac));
    set_flag(m, FLAG_OVERFLOW, t1 & 0x40);
    set_flag(m, FLAG_NEGATIVE, t1 & 0x80);
    break;

case RMB0:
    m->mem[NEXT_BYTE(m)] &= ~0x01;
    break;

case RMB1:
    m->mem[NEXT_BYTE(m)] &= ~0x02;
    break;

case RMB2:
    m->mem[NEXT_BYTE(m)] &= ~0x04;
    break;

case RMB3:
    m->mem[NEXT_BYTE(m)] &= ~0x08;
    break;

case RMB4:
    m->mem[NEXT_BYTE(m)] &= ~0x10;
    break;

case RMB5:
    m->mem[NEXT_BYTE(m)] &= ~0x20;
    break;

case RMB6:
    m->mem[NEXT_BYTE(m)] &= ~0x40;
    break;

case RMB7:
    m->mem[NEXT_BYTE(m)] &= ~0x80;
    break;

case SMB0:
    m->mem[NEXT_BYTE(m)] |= 0x01;
    break;

case SMB1:
    m->mem[NEXT_BYTE(m)] |= 0x02;
    break;

case SMB2:
    m->mem[NEXT_BYTE(m)] |= 0x04;
    break;

case SMB3:
    m->mem[NEXT_BYTE(m)] |= 0x08;
    break;

case SMB4:
    m->mem[NEXT_BYTE(m)] |= 0x10;
    break;

case SMB5:
    m->mem[NEXT_BYTE(m)] |= 0x20;
    break;

case SMB6:
    m->mem[NEXT_BYTE(m)] |= 0x40;
    break;

case SMB7:
    m->mem[NEXT_BYTE(m)] |= 0x80;
    break;

case TRB_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    set_flag(m, FLAG_ZERO, m->mem[mem_abs(arg1, arg2, 0)] & m->ac);
    m->mem[mem_abs(arg1, arg2, 0)] &= ~m->ac;
    break;

case TRB_ZP:
    t1 = NEXT_BYTE(m);
    set_flag(m, FLAG_ZERO, m->mem[t1] & m->ac);
    m->mem[t1] &= ~m->ac;
    break;

case TSB_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    set_flag(m, FLAG_ZERO, m->mem[mem_abs(arg1, arg2, 0)] & m->ac);
    m->mem[mem_abs(arg1, arg2, 0)] |= m->ac;
    break;

case TSB_ZP:
    t1 = NEXT_BYTE(m);
    set_flag(m, FLAG_ZERO, m->mem[t1] & m->ac);
    m->mem[t1] |= m->ac;
    break;
