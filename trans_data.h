#ifndef TRANS_DATA_H
#define TRANS_DATA_H

#include "session.h"

int get_trans_data_fd(session_t *sess);
void trans_list(session_t *sess, int list);

#endif /* TRANS_DATA_H */