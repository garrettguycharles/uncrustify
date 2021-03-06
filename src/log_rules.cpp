/**
 * @file log_rules.cpp
 * is an extract from space.cpp
 *
 * @author  Guy Maurel
 * @license GPL v2+
 */

#include "log_rules.h"
#include <string.h>


void log_rule2(const char *func, size_t line, const char *rule, chunk_t *first, chunk_t *second)
{
   LOG_FUNC_ENTRY();

   if (second->type != CT_NEWLINE)
   {
      LOG_FMT(LSPACE, "%s(%zu): first->orig_line is %zu, first->orig_col is %zu, first->text() is '%s', [%s/%s] <===>\n",
              func, line, first->orig_line, first->orig_col, first->text(),
              get_token_name(first->type), get_token_name(get_chunk_parent_type(first)));
      LOG_FMT(LSPACE, "   second->orig_line is %zu, second->orig_col is %zu, second->text() '%s', [%s/%s] : rule %s[line %zu]\n",
              second->orig_line, second->orig_col, second->text(),
              get_token_name(second->type), get_token_name(get_chunk_parent_type(second)),
              rule, line);
   }
}


void log_rule3(const char *func, const char *rule)
{
   const char *where = nullptr;

#ifdef WIN32
   // some Windows provide "ABC::XYZ::function_Name" as __func__
   // we look for the last ':' character
   // a function rindex cannot be found
   size_t length_of_string = strlen(func);

   for (int which = length_of_string - 1; which > 0; which--)
   {
      char oneChar = func[which];

      if (oneChar == ':')
      {
         where = func + which;
         break;
      }
   }
#else // not WIN32
   where = rindex(func, ':');
#endif /* ifdef WIN32 */

   if (where == nullptr)
   {
      LOG_FMT(LSPACE, "log_rule(%s): rule is '%s'\n", func, rule);
   }
   else
   {
      LOG_FMT(LSPACE, "log_rule(%s): rule is '%s'\n", where + 1, rule);
   }
}
