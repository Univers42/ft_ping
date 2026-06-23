# Function to create directory structure
define create_dirs
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	# NOTE: do not create $(BUILD_DIR) automatically to avoid polluting the repo
	# If you really need build/ for tools, create it manually or via an explicit target.
endef

# Function to print status messages (single-line to avoid breaking shell blocks)
define print_status
	printf '%s%s%s[%s%s%s]%s: %s%s\n' "$(FADED_BOLD_GRAY)$(notdir $(CURDIR))$(FADED_BOLD_GRAY)" "$(1)" "$(2)" "$(FADED_BOLD_GRAY)$(FADED_BOLD_GRAY)$(WHITE)$(3)$(RESET)"
endef

# General logging macro (single-line)
define logging
	printf '%s%s%s[%s%s%s]%s: %s%s\n' "$(FADED_BOLD_GRAY)$(notdir $(CURDIR))$(FADED_BOLD_GRAY)" "$(1)" "$(2)" "$(FADED_BOLD_GRAY)$(FADED_BOLD_GRAY)$(WHITE)$(3)$(RESET)"
endef

# Function to clean object files (use rm -rf to remove directory reliably)
define clean_objects
	@$(call print_status,$(RED),CLEAN,Removing object files...)
	@rm -rf $(OBJ_DIR)
endef

# Function to clean library
define clean_library
	@$(call print_status,$(RED),CLEAN,Removing library $(NAME)...)
	@$(RM) $(NAME)
endef

# Logging macros for formatted output
log_note = @printf "$(BOLD_MAGENTA)%s$(RESET)\n" "$(1)"
log_info = @printf "$(BOLD_GREEN)%s$(RESET)\n" "$(1)"
log_ok = @printf "  $(BRIGHT_CYAN)✓$(RESET) %s\n" "$(1)"
log_warn = @printf "$(BRIGHT_YELLOW)⚠ %s$(RESET)\n" "$(1)"
log_error = @printf "$(BRIGHT_RED)✗ %s$(RESET)\n" "$(1)"

# Print a centered, colored title banner.
# Usage: $(call log_title,Your Title Here)
log_title = @printf "$(BOLD_CYAN)╔════════════════════════════════════════════════════════╗$(RESET)\n"; \
             printf "$(BOLD_CYAN)║$(RESET)  $(BOLD_YELLOW)%-46s$(RESET)  $(BOLD_CYAN)	 ║$(RESET)\n" "$(1)"; \
             printf "$(BOLD_CYAN)╚════════════════════════════════════════════════════════╝$(RESET)\n"